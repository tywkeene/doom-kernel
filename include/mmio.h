#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

void mmio_write32(uint32_t reg, uint32_t data);
uint32_t mmio_read32(uint32_t reg);

#endif
