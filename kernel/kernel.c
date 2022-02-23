#include <stddef.h>
#include <stdint.h>

#include "../include/kernel.h"
#include "../include/printk.h"
#include "../include/uart.h"
#include "../include/mmio.h"
#include "../include/mmap.h"
#include "../include/gic.h"
#include "../include/status.h"

extern uint32_t _asm_get_cpu_id();
extern uint32_t _asm_get_cpu_revision_id();
extern uint32_t _asm_get_cpu_features();
extern uint32_t _asm_get_board_info();
extern uint32_t _asm_read_peripheral_base_addr();
extern uint32_t _asm_enable_interrupts();

static const char *edgy_pentagram = \
"                   .......                   \n"
"            .....          .....             \n"
"         ....                   ...          \n"
"       ...  .                    . ...       \n"
"     ...     ..               ...    ..      \n"
"    ..       .....         .....      ...    \n"
"   ..         .   ..     ..   ..       ...   \n"
"  ..          ..    ....     ..         ...  \n"
" ...           ..  ... ..   ..           ..  \n"
" ..            ....       ....           ... \n"
" ..           ....  DOOM   ....          ... \n"
" ..        ...                 ...       ... \n"
" ..     ...      ..       ..      ...    ... \n"
" ...  .................................  ..  \n"
"  ..               .    ..              ...  \n"
"   ..              ..   ..             ...   \n"
"    ..              .  ..             ...    \n"
"       ...           ...           ...       \n"
"         ....         .         ...          \n"
"            .....     .    .....             \n"
"                   .......                   \n"
"            Doom Kernel booting...           \n";

static uint32_t get_bits(uint32_t n, uint32_t bitmask)
{
    uint32_t result = 0;
    int i = 0;
    for (i = 31; i >= 0; i--)
        if (bitmask & (1u << i))
            result = result * 2 + ((n & (1u << i)) ? 1 : 0);
    return result;
}

uint32_t get_core_count()
{
    volatile uint32_t reg;
    asm volatile("mrc p15, 1, %[out], c9, c0, 2" : [out] "=r" (reg));
    // Looks weird but this is an easier way to implement
    // converting a decimal from binary, at least for 4 bits.
    // The manual states that 0 == 1 core, 1 == 2, etc.
    static int num_cores[4] = { [0] = 1, [1] = 2, [2] = 3, [3] = 4};
    return num_cores[ get_bits(reg, ((1 << 24) | (1 << 25)) )];
}

void print_cpu_features()
{
    volatile uint32_t value;

    // Detect instruction set support
    asm volatile("mrc p15, 0, %[out], c0, c1, 0" : [out] "=r" (value));
    printk("Supports ARM instruction set: %#08x\n", get_bits(value, ((1 << 0) | (1 << 1)|(1 << 2)|(1 << 3))) );
    printk("Supports THUMB instruction set: %#08x\n", get_bits(value, ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))) );

    // Get core count
    asm volatile("mrc p15, 1, %[out], c9, c0, 2" : [out] "=r" (value));
    // Looks weird but this is an easier way to implement
    // converting a decimal from binary, at least for 4 bits.
    // The manual states that 0 == 1 core, 1 == 2, etc.
    static int num_cores[4] = { [0] = 1, [1] = 2, [2] = 3, [3] = 4};
    printk("%d cores\n", num_cores[ get_bits(value, ((1 << 24) | (1 << 25)))]);
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    uart_init();
    print_cpu_features();

    printk("%s\n", edgy_pentagram);
    printk("Peripheral base address: %#08x\n", _asm_read_peripheral_base_addr());

    enable_global_interrupt_controller();
    gic_enable_interrupt(37);
    asm volatile("cpsie if");

    int a = 1 / 0;
    while(1);
    // run_doom() goes here
}
