#include <stddef.h>
#include <stdint.h>

#include "../include/kernel.h"
#include "../include/printk.h"
#include "../include/uart.h"

status_byte_t kernel_status;

extern uint32_t _asm_get_cpu_id();
extern uint32_t _asm_get_cpu_revision_id();
extern uint32_t _asm_get_cpu_features();
extern uint32_t _asm_get_l2_ctrl_reg();

// A Mailbox message with set clock rate of PL011 to 3MHz tag
volatile unsigned int  __attribute__((aligned(16))) mbox[9] = {
    9*4, 0, 0x38002, 12, 8, 2, 3000000, 0 ,0
};

inline void set_kernel_status_on(uint8_t bit) {
    kernel_status |= (1 << bit);
}

inline void set_kernel_status_off(uint8_t bit) {
    kernel_status &= ~(1 << bit);
}

_Bool check_kernel_status(uint8_t bit) {
    return kernel_status & (1 << bit);
}

void dump_kernel_status(void) {
    printk("Kernel status byte: RES:0000000 UART:%d\n",
            check_kernel_status(KERN_STATUS_UART));
}

static uint32_t get_bits(uint32_t n, uint32_t bitmask) {
	uint32_t result = 0;
	int i = 0;
	for (i = 31; i >= 0; i--)
		if (bitmask & (1u << i))
			result = result * 2 + ((n & (1u << i)) ? 1 : 0);
	return result;
}

void print_L2_info(){
    volatile uint32_t l2_reg = _asm_get_l2_ctrl_reg();

    static char * const ram_latency[2] = {
        [0x0] = "2 cycles",
        [0x1] = "3 cycles",
    };

    // Looks weird but this is an easier way to implement
    // converting a decimal from binary. The manual states
    // that 0 == 1 core, 1 == 2, etc.
    // 
    // See the "L2 Control Register" section of the ARM manual
    static int num_cores[4] = {
        [0] = 1,
        [1] = 2,
        [2] = 3,
        [3] = 4,
    };

    char *latency_str = ram_latency[get_bits(l2_reg, (1 << 0))];
    int cores = num_cores[get_bits(l2_reg, ((1 << 24) | (1 << 25)) )];

    printk("RAM Latency: %s\n", latency_str);
    printk("Interrupt Controller Present: %u\n", get_bits(l2_reg, ((1 << 23))));
    printk("Cores: %d\n", cores);
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
    uart_init();

    char *boot_message = "Doom Kernel booting...";
    printk("%s\n", boot_message);

    print_L2_info();
    dump_kernel_status();
    while(1)
        uart_putc(uart_getc());
    // run_doom() goes here
}
