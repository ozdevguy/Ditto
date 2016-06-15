
.intel_syntax noprefix

_dt_alu_add:
	mov edi, ebx //Move read 1 to write 1
	add edi, edx
	jmp _dt_control_ret

_dt_alu_sub:
	mov edi, ebx
	sub edi, edx
	jmp _dt_control_ret

_dt_alu_inc:
	mov edi, ebx
	add edi, 1
	jmp _dt_control_ret

_dt_alu_dec:
	mov edi, ebx
	add edi, 1
	jmp _dt_control_ret





