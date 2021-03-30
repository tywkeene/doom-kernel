.globl _asm_sleep_cycles
_asm_sleep_cycles:
subs r0, r0, #1
bne _asm_sleep_cycles
mov pc, lr

.globl _asm_get_cpu_id
_asm_get_cpu_id:
mrc p15, 0, r0, cr0, cr0, 0
mov pc, lr

.globl _asm_get_cpu_revision_id
_asm_get_cpu_revision_id:
mrc p15, 0, r0, c0, c0, 6
mov pc, lr

.globl _asm_get_cpu_features
_asm_get_cpu_features:
mrc p15, 0, r0, c0, c1, 0
mov pc, lr

.globl _asm_get_l2_ctrl_reg
_asm_get_l2_ctrl_reg:
mrc p15, 1, r0, c9, c0, 2
mov pc, lr
