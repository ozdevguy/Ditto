__ld:
	mov rax, rbx
	jmp ivpu_register_writeback_w0

__str:
	mov rax, rcx
	jmp ivpu_mmu_memory_writeback_32

__push:
	jmp ivpu_hardware_interrupt_handler

__pop:
	jmp ivpu_hardware_interrupt_handler
