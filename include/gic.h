#ifndef GIC_H
#define GIC_H

#include <stdint.h>

extern uint32_t _asm_read_peripheral_base_addr();

typedef volatile struct __attribute__((packed)) {
    uint32_t DCTLR;                 /* 0x0 Distributor Control register */
    const uint32_t DTYPER;          /* 0x4 Controller type register */
    const uint32_t DIIDR;           /* 0x8 Implementer identification register */
    uint32_t _reserved0[29];        /* 0xC - 0x80; reserved and implementation-defined */
    uint32_t DIGROUPR[32];          /* 0x80 - 0xFC Interrupt group registers */
    uint32_t DISENABLER[32];        /* 0x100 - 0x17C Interrupt set-enable registers */
    uint32_t DICENABLER[32];        /* 0x180 - 0x1FC Interrupt clear-enable registers */
    uint32_t DISPENDR[32];          /* 0x200 - 0x27C Interrupt set-pending registers */
    uint32_t DICPENDR[32];          /* 0x280 - 0x2FC Interrupt clear-pending registers */
    uint32_t DICDABR[32];           /* 0x300 - 0x3FC Active Bit Registers (GIC v1) */
    uint32_t _reserved1[32];        /* 0x380 - 0x3FC reserved on GIC v1 */
    uint32_t DIPRIORITY[255];       /* 0x400 - 0x7F8 Interrupt priority registers */
    uint32_t _reserved2;            /* 0x7FC reserved */
    const uint32_t DITARGETSRO[8];  /* 0x800 - 0x81C Interrupt CPU targets, RO */
    uint32_t DITARGETSR[246];       /* 0x820 - 0xBF8 Interrupt CPU targets */
    uint32_t _reserved3;            /* 0xBFC reserved */
    uint32_t DICFGR[64];            /* 0xC00 - 0xCFC Interrupt config registers */
    /* Some PPI, SPI status registers and identification registers beyond this.
       Don't care about them */
} gic_distributor_registers;

typedef volatile struct __attribute__((packed)) {
    uint32_t CCTLR;                 /* 0x0 CPU Interface control register */
    uint32_t CCPMR;                 /* 0x4 Interrupt priority mask register */
    uint32_t CBPR;                  /* 0x8 Binary point register */
    const uint32_t CIAR;            /* 0xC Interrupt acknowledge register */
    uint32_t CEOIR;                 /* 0x10 End of interrupt register */
    const uint32_t CRPR;            /* 0x14 Running priority register */
    const uint32_t CHPPIR;          /* 0x18 Higher priority pending interrupt register */
    uint32_t CABPR;                 /* 0x1C Aliased binary point register */
    const uint32_t CAIAR;           /* 0x20 Aliased interrupt acknowledge register */
    uint32_t CAEOIR;                /* 0x24 Aliased end of interrupt register */
    const uint32_t CAHPPIR;         /* 0x28 Aliased highest priority pending interrupt register */
} gic_cpu_interface_registers;

#define GIC_BASE_ADDR           (_asm_read_peripheral_base_addr() + 0x1000)
#define CPU_IFACE_ADDR          (_asm_read_peripheral_base_addr() + 0x2000)

#define GICD_CTRL               (GIC_BASE_ADDR)
#define GICD_TYPE_R             (GIC_BASE_ADDR +  0x004)
#define GICD_IIDR               (GIC_BASE_ADDR +  0x008)
#define GICD_IGROUP_BASE        (GIC_BASE_ADDR +  0x080)
#define GICD_ENABLER_BASE       (GIC_BASE_ADDR +  0x100)
#define GICD_ISPEND_BASE        (GIC_BASE_ADDR +  0x200)
#define GICD_ICPEND_BASE        (GIC_BASE_ADDR +  0x280)
#define GICD_ISACTIVE_BASE      (GIC_BASE_ADDR +  0x280)
#define GICD_ICACTIVE_BASE      (GIC_BASE_ADDR +  0x380)
#define GICD_IPRIORITY_BASE     (GIC_BASE_ADDR +  0x400)
#define GICD_ITARGETS_BASE      (GIC_BASE_ADDR +  0x800)
#define GICD_ICFG_BASE          (GIC_BASE_ADDR +  0xC00)
#define GICD_PPISR              (GIC_BASE_ADDR +  0xD00)
#define GICD_SPISR              (GIC_BASE_ADDR +  0xD04)
#define GICD_SGIR               (GIC_BASE_ADDR +  0xF00)
#define GICD_CGIR_CPENDSGI      (GIC_BASE_ADDR +  0xF10)
#define GICD_SGIR_CPENDSGI      (GIC_BASE_ADDR +  0xF20)

void gic_enable_interrupt(uint8_t number);
void enable_global_interrupt_controller(void);

#endif
