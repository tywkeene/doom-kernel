#include "../include/printk.h"
#include "../include/gic.h"
#include "../include/mmio.h"
#include "../include/status.h"

gic_distributor_registers *gic_dregs;
gic_cpu_interface_registers *gic_ifregs;

void __attribute__((interrupt)) uart_isr(void *ptr)
{
    printk("Interrupt! %08x\n", ptr);
}

void gic_enable_interrupt(uint8_t number)
{
    /* Enable the interrupt */
    uint8_t reg = number / 32;
    uint8_t bit = number % 32;

    uint32_t reg_val = gic_dregs->DISENABLER[reg];
    reg_val |= (1u << bit);
    mmio_write32(gic_dregs->DISENABLER[reg], reg_val);

    /* Forward interrupt to CPU Interface 0 */
    reg = number / 4;
    bit = (number % 4) * 8; /* Can result in bit 0, 8, 16 or 24 */
    reg_val = gic_dregs->DITARGETSR[reg];
    reg_val |= (1u << bit);
    mmio_write32(gic_dregs->DITARGETSR[reg], reg_val);
}

void enable_global_interrupt_controller(void)
{
    gic_ifregs = (gic_cpu_interface_registers*) GIC_BASE_ADDR;
    gic_dregs = (gic_distributor_registers*) GIC_BASE_ADDR;

    mmio_write32(gic_ifregs->CCPMR, 0xFFFFFFFF); /* Enable all interrupt priorities */
    mmio_write32(gic_ifregs->CCTLR, 0x01); /* Enable interrupt forwarding to this CPU */

    gic_distributor_registers* gic_dregs = (gic_distributor_registers*) GIC_BASE_ADDR;
    mmio_write32(gic_dregs->DCTLR, 0x01); /* Enable the interrupt distributor */
}
