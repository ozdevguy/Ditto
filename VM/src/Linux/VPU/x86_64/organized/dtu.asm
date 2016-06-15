__ld:
	mov rax, rcx								#Move the value in the read buffer into the write buffer.
	jmp ivpu_register_writeback_w0				#The load instruction writes a value from memory to the register specified for w0, so we jump to the appropriate writeback function.

__str:
	mov rax, rcx
	jmp ivpu_mmu_writeback

__push:
	mov rax, 0x100000						#Create an instruction architecture mask.
	and rax, r15							#Get the instruction architecture by applying the mask.
	cmp rax, 0x0							#Compare the instruction architecture to 0.
	je ivpu_mmu_stack_push_32				#If 0, this is a 32 bit push instruction.
	jmp ivpu_mmu_stack_push_64				#If not 0, this is a 64 bit push instruction.

	ivpu_push_ret:
		#jmp ivpu_mmu_writeback_null

__pop:
	mov rax, 0x100000						#Create an instruction architecture mask
	and rax, r15							#Apply the mask to the instruction.
	cmp rax, 0x0							#Compare the architecture value to zero.
	je ivpu_mmu_stack_pop_32				#Perform 32 bit stack pop.
	jmp ivpu_mmu_stack_pop_64				#Perform 64 bit stack pop.
	
	ivpu_pop_ret:
		#jmp ivpu_mmu_writeback_w0


__stop:
	jmp [r14 + 2072]


