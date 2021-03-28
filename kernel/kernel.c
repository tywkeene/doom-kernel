#include <stddef.h>
#include <stdint.h>

#include "../include/kernel.h"
#include "../include/printk.h"
#include "../include/uart.h"

status_byte_t kernel_status;

// A Mailbox message with set clock rate of PL011 to 3MHz tag
volatile unsigned int  __attribute__((aligned(16))) mbox[9] = {
    9*4, 0, 0x38002, 12, 8, 2, 3000000, 0 ,0
};

inline void set_kernel_status_on(uint8_t bit)
{
    kernel_status |= (1 << bit);
}

inline void set_kernel_status_off(uint8_t bit)
{
    kernel_status &= ~(1 << bit);
}

_Bool check_kernel_status(uint8_t bit)
{
    return kernel_status & (1 << bit);
}

void dump_kernel_status(void)
{
    printk("Kernel status byte: RES:0000000 UART:%d\n",
            check_kernel_status(KERN_STATUS_UART));
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
    uart_init();

    char *boot_message = "Doom Kernel booting...";
    printk("%s\r\n", boot_message);
    dump_kernel_status();
    uart_disable();

    while(1)
        uart_putc(uart_getc());
}
