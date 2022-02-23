#include "../include/status.h"
#include "../include/printk.h"

status_byte_t kernel_status;

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
    printk("Kernel status byte: RES:000000 GIC: %d UART: %d\n",
            check_kernel_status(KERN_STATUS_GIC),
            check_kernel_status(KERN_STATUS_UART));
}
