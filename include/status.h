#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

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
   |2 GIC              |    Is the Global Interrupt Controller enabled?
   |3 RESERVED         |
   |4 RESERVED         |
   |5 RESERVED         |
   |6 RESERVED         |
   |7 RESERVED         |
   |8 RESERVED         |
   +-------------------+
 */

/*Kernel status bits*/
#define KERN_STATUS_UART    0
#define KERN_STATUS_GIC     1
#define KERN_STATUS_RES_3   2
#define KERN_STATUS_RES_4   3
#define KERN_STATUS_RES_5   4
#define KERN_STATUS_RES_6   5
#define KERN_STATUS_RES_7   6
#define KERN_STATUS_RES_8   7

/*Function Prototypes*/
void set_kernel_status_on(uint8_t);
void set_kernel_status_off(uint8_t);
_Bool check_kernel_status(uint8_t);
void dump_kernel_status(void);

#endif
