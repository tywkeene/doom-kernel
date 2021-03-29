.globl _asm_get_cpu_id
.globl _asm_get_cpu_revision_id
.globl _asm_get_cpu_features
.globl _asm_get_l2_ctrl_reg

_asm_get_cpu_id:
mrc p15, 0, r0, cr0, cr0, 0
mov pc, lr

_asm_get_cpu_revision_id:
mrc p15, 0, r0, c0, c0, 6
mov pc, lr

_asm_get_cpu_features:
mrc p15, 0, r0, c0, c1, 0
mov pc, lr

_asm_get_l2_ctrl_reg:
mrc p15, 1, r0, c9, c0, 2
mov pc, lr
