ivpu_mmu_writeback:
	mov rdx, 0x100000						#Create an instruction architecture mask
	and rdx, r15							#Apply the mask to the instruction.
	cmp rdx, 0x0
	je ivpu_mmu_writeback_32
	jmp ivpu_mmu_writeback_64


ivpu_mmu_writeback_32:
	mov dword ptr [r13 + rbx], eax
	mov rax, rsi									#Copy the FLAGS register into rax.
	shr rax, 0x16									#Shift the FLAGS register right by 22 in order to get the instruction layout bits.
	cmp rax, 0x0									#Compare the value in RAX to 0.
	je ivpu_adjust_ip_4								#If the value in RAX is 0, increment the instruction pointer by 4.
	cmp rax, 0x2									#Compare the value in rax to 2
	jmp ivpu_adjust_ip_8							#If the value in RAX is 2, increment the instruction pointer by 8.

ivpu_mmu_writeback_64:
	mov qword ptr [r13 + rbx], rax
	mov rax, rsi									#Copy the FLAGS register into rax.
	shr rax, 0x16									#Shift the FLAGS register right by 22 in order to get the instruction layout bits.
	cmp rax, 0x1									#Compare the value in RAX to 1.									#Compare the value in rax to 1.
	je ivpu_adjust_ip_8								#If the value in RAX is 1, increment the instruction pointer by 8.
	cmp rax, 0x3									#Compare the value in rax to 3.
	jmp ivpu_adjust_ip_16							#If the value in RAX is 3, increment the instruction pointer by 16. 
	

ivpu_mmu_stack_push_32:
	mov eax, dword ptr [r14d + 2192]				#Get the address in the stack pointer.
	cmp r12, rax									#Check to make sure the address falls within the appropriate range.
	jl ivpu_memory_range_fault_handler				#If the address is out of bounds, perform an memory range fault.
	mov dword ptr [r13d + eax], ecx					#Push the item to the stack.
	add eax, 0x4									#Increment the stack pointer by 4.
	mov dword ptr [r14d + 2192], eax					#Store the new stack pointer.
	jmp ivpu_push_ret								#Return to the executing function.


ivpu_mmu_stack_push_64:
	mov rax, qword ptr [r14 + 2192]				#Get the address in the stack pointer.
	cmp r12, rax									#Check to make sure the address falls within the appropriate range.
	jl ivpu_memory_range_fault_handler				#If the address is out of bounds, perform an memory range fault.
	mov qword ptr [r13 + rax], rcx					#Push the item to the stack.
	add rax, 0x8									#Increment the stack pointer by 4.
	mov qword ptr [r14 + 2192], rax					#Store the new stack pointer.
	jmp ivpu_push_ret								#Return the the executing function.
