#include <stddef.h>
#include <stdint.h>

#include "../include/kernel.h"
#include "../include/printk.h"
#include "../include/uart.h"

// A Mailbox message with set clock rate of PL011 to 3MHz tag
volatile unsigned int  __attribute__((aligned(16))) mbox[9] = {
    9*4, 0, 0x38002, 12, 8, 2, 3000000, 0 ,0
};

void kernel_initialize_mmu(){}
void kernel_initialize_fpu(){}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
    uart_init();
    char *boot_message = "Doom Kernel booting...";
    printk("%s\r\n", boot_message);

    while(1)
        uart_putc(uart_getc());
}
