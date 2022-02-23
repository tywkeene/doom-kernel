#include <stddef.h>
#include <stdint.h>

#include "../include/uart.h"
#include "../include/mmio.h"
#include "../include/status.h"

extern void _asm_sleep_cycles(uint32_t n);

void uart_init() {
    if (check_kernel_status(KERN_STATUS_UART) == 1)
        return;

    uart_disable();

    // Setup the GPIO pin 14 && 15.
    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    mmio_write32(GPPUD, 0x00000000);
    _asm_sleep_cycles(150);

    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    mmio_write32(GPPUDCLK0, (1 << 14) | (1 << 15));
    _asm_sleep_cycles(150);

    // Write 0 to GPPUDCLK0 to make it take effect.
    mmio_write32(GPPUDCLK0, 0x00000000);

    // Clear pending interrupts.
    mmio_write32(UART0_ICR, 0x7FF);

    // Set integer & fractional part of baud rate.
    // Divider = UART_CLOCK/(16 * Baud)
    // Fraction part register = (Fractional part * 64) + 0.5
    // Baud = 115200.

    // Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
    mmio_write32(UART0_IBRD, 1);
    // Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
    mmio_write32(UART0_FBRD, 40);

    // Enable FIFO & 8 bit data transmission (1 stop bit, no parity).
    mmio_write32(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    // Mask all interrupts.
    mmio_write32(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    uart_enable();
    set_kernel_status_on(KERN_STATUS_UART);
}

static inline void uart_wait_read(){
    // Wait for UART to have received something.
    while(mmio_read32(UART0_FR) & (1 << 4)){}
}

static inline void uart_wait_write(){
    // Wait for UART to become ready to transmit.
    while(mmio_read32(UART0_FR) & (1 << 5)) {}
}

void uart_enable(){
    if (check_kernel_status(KERN_STATUS_UART) == 1)
        return;
    // Enable UART0, receive & transfer part of UART.
    mmio_write32(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
    set_kernel_status_on(KERN_STATUS_UART);
}

void uart_disable(){
    if (check_kernel_status(KERN_STATUS_UART) == 0)
        return;
    // Disable UART0 by writing 0 to the Control Register
    mmio_write32(UART0_CR, 0x00000000);
    set_kernel_status_off(KERN_STATUS_UART);
}

void uart_putc(unsigned char c) {
    if (check_kernel_status(KERN_STATUS_UART) == 0)
        return;
    uart_wait_write();
    mmio_write32(UART0_DR, c);
}

unsigned char uart_getc() {
    if (check_kernel_status(KERN_STATUS_UART) == 0)
        return 0x00;
    uart_wait_read();
    return mmio_read32(UART0_DR);
}

void uart_puts(const char* str) {
    if (check_kernel_status(KERN_STATUS_UART) == 0)
        return;
    for(size_t i = 0; str[i] != '\0'; i++)
        uart_putc((unsigned char)str[i]);
}
