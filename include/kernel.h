#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdint.h>

#define  MMIO_BASE      0x3F000000

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

// Types

typedef char status_byte_t;

/*
 Each bit represented below is initialzed to 0 when kmain() is called
 The bits 2 through 8 are reserved for future use and not currently used, 
 therefor their state is undefined
   +-------------------+
   |kern_status        |
   |-------------------|
   |1 UART             | 	Is UART configurated and enabled?
   |2 RESERVED         |
   |3 RESERVED         |
   |4 RESERVED         |
   |5 RESERVED         |
   |6 RESERVED         |
   |7 RESERVED         |
   |8 RESERVED         |
   +-------------------+
 */

/*Kernel status bits*/
#define KERN_STATUS_UART    1
#define KERN_STATUS_RES_2   2
#define KERN_STATUS_RES_3   3
#define KERN_STATUS_RES_4   4
#define KERN_STATUS_RES_5   5
#define KERN_STATUS_RES_6   6
#define KERN_STATUS_RES_7   7
#define KERN_STATUS_RES_8   8

/*Function Prototypes*/
void set_kernel_status_on(uint8_t);
void set_kernel_status_off(uint8_t);
_Bool check_kernel_status(uint8_t);
void dump_kernel_status(void);

#endif
