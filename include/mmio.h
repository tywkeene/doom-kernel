#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

void mmio_write32(uint32_t reg, uint32_t data);
uint32_t mmio_read32(uint32_t reg);

#define MMIO_BASE           0x3F000000

// GIC memory map
#define VCPU_DISTRIB                (MMIO_BASE + 0x1000)	// Distributor
#define CPU_INTERFACE               (MMIO_BASE + 0x2000)	// CPU interface
#define COMMON_VCPU_INTERFACE_CTL   (MMIO_BASE + 0x4000)	// Virtual interface control, common base address
#define SPECIFIC_VCPU_INTERFACE_CTL (MMIO_BASE + 0x5000)	// Virtual interface control, processor-specific base address
#define VCPU_INTERFACE              (MMIO_BASE + 0x6000)	// Virtual CPU interface

#define  GPIO_BASE      (MMIO_BASE + 0x200000)
#define  GPPUD          (GPIO_BASE + 0x94)
#define  GPPUDCLK0      (GPIO_BASE + 0x98)

#define  UART0_BASE     (GPIO_BASE + 0x1000)
#define  UART0_DR       (UART0_BASE + 0x00) // UART data read register
#define  UART0_RSRECR   (UART0_BASE + 0x04) // Receive Status Register/Error Clear Register
#define  UART0_FR       (UART0_BASE + 0x18) // Flag Register/Shows status of FIFO
#define  UART0_ILPR     (UART0_BASE + 0x20)
#define  UART0_IBRD     (UART0_BASE + 0x24)
#define  UART0_FBRD     (UART0_BASE + 0x28)
#define  UART0_LCRH     (UART0_BASE + 0x2C)
#define  UART0_CR       (UART0_BASE + 0x30) // UART control register
#define  UART0_IFLS     (UART0_BASE + 0x34)
#define  UART0_IMSC     (UART0_BASE + 0x38)
#define  UART0_RIS      (UART0_BASE + 0x3C)
#define  UART0_MIS      (UART0_BASE + 0x40)
#define  UART0_ICR      (UART0_BASE + 0x44) // Interrupt Clear Register/Write only
                                            // A write of zero has no effect.
#define  UART0_DMACR    (UART0_BASE + 0x48)
#define  UART0_ITCR     (UART0_BASE + 0x80)
#define  UART0_ITIP     (UART0_BASE + 0x84)
#define  UART0_ITOP     (UART0_BASE + 0x88)
#define  UART0_TDR      (UART0_BASE + 0x8C)

#define  MBOX_BASE      (MMIO_BASE + 0xB880)
#define  MBOX_READ      (MBOX_BASE + 0x00)
#define  MBOX_STATUS    (MBOX_BASE + 0x18)
#define  MBOX_WRITE     (MBOX_BASE + 0x20)

#endif
