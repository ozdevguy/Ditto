
__add:
	add rcx, rbx
	mov rax, rcx
	jmp ivpu_register_writeback_w0


__mov:
	add rax, rbx
	jmp ivpu_register_writeback_w0

