// Misc. useful functions
.globl _asm_sleep_cycles
_asm_sleep_cycles:
subs r0, r0, #1
bne _asm_sleep_cycles
bx lr

// System control subroutines
.globl _asm_read_peripheral_base_addr
_asm_read_peripheral_base_addr:
mrc p15, 4, r0, c15, c0, 0
bx lr

.globl _asm_get_cpu_id
_asm_get_cpu_id:
mrc p15, 0, r0, cr0, cr0, 0
bx lr

.globl _asm_get_cpu_revision_id
_asm_get_cpu_revision_id:
mrc p15, 0, r0, c0, c0, 6
bx lr

.globl _asm_get_cpu_features
_asm_get_cpu_features:
mrc p15, 0, r0, c0, c1, 0
bx lr

.globl _asm_get_board_info
_asm_get_board_info:
push {r5-r7,lr}
mrc p15, 1, r0, c9, c0, 2
pop {r5-r7,pc}
bx lr

.global _asm_enable_interrupts
_asm_enable_interrupts:
push {r5-r7,lr}
cpsie if
pop {r5-r7,pc}
bx lr

.global _asm_disable_interrupts
_asm_disable_interrupts:
push {r5-r7,lr}
cpsid if
pop {r5-r7,pc}
bx lr
