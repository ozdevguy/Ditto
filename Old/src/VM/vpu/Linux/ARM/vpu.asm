.data

.text

.include "alu/addsub.asm"

.global _vpu_start

_vpu_start:
	ldr r5, =_dt_alu_inc
	mov r2, r1
	mov r1, r0
	bx r5

_dt_control_ret:
	mov r0, r3
	mov r5, r14
	b _intTest

cont:
	mov r14, r5	
	bx lr


