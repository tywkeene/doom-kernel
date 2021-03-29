#include <stddef.h>
#include <stdint.h>

#include "../include/mmio.h"

// Memory-Mapped I/O output
void mmio_write32(uint32_t reg, uint32_t data) {
    *(volatile uint32_t*) reg = data;
}

// Memory-Mapped I/O input
uint32_t mmio_read32(uint32_t reg) {
    return *(volatile uint32_t*) reg;
}
