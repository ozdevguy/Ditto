

#Privileged mode instruction fetch.
ivpu_mmu_fetch_instruction_priv:						#Fetch the next instruction from memory in privileged mode.
	cmp r12, rdi										#Compare the current instruction pointer to the attached memory size.
	jle ivpu_memory_range_fault_handler                 #If the given instruction pointer is out of bounds, trigger a memory range fault.
	mov r15, qword ptr [r13 + rdi]						#Copy the instruction from memory into the instruction register.
	jmp ivpu_decoder_dispatch							#Dispatch the instruction decoder.


ivpu_mmu_stack_pop_32:
	mov rbx, 0x0
	mov ebx, [r14d + 2192]				#Get the value of the stack pointer register.
	cmp r12, rbx
	jl ivpu_memory_range_fault_handler
	mov rax, [r13 + rbx]				#Get the word located at the stack address.
	sub rbx, 0x4
	mov [r14d + 2192], ebx
	jmp ivpu_pop_ret

ivpu_mmu_stack_pop_64:
	mov rbx, [r14 + 2192]
	cmp r12, rbx
	jl ivpu_memory_range_fault_handler
	mov rax, [r13 + rbx]
	sub rbx, 0x8
	mov [r14 + 2192], rbx
	jmp ivpu_pop_ret




#Protected mode instruction fetch.
ivpu_mmu_fetch_instruction_prot:						#Fetch the next instruction from memory in protected mode.
	jmp ivpu_hardware_interrupt_handler




#Read a 32  bit instruction immediate (next word), and place it on read 1.
ivpu_mmu_read_inst_imm32:
	test rsi, 0x2000									#Create a mask for the PR flag in the FLAGS register.
	jnz ivpu_mmu_read_imm32_prot                        #If the PR flag has been set, we need to execute this in protected mode.
	mov rdx, rdi										#Move the instruction pointer into rdx.
	add rdx, 0x4										#Add 4 to rdx in order to get the address of the second word.
	cmp r12, rdx										#Compare the address in rdx to the memory limit.
	jl ivpu_memory_range_fault_handler					#If the memory address is out of bounds, trigger a memory range fault.
	mov ebx, [r13 + rdx]								#Move the data in the second word into read 0.
	jmp ivpu_execute

	#32 bit instruction immediate read in protected mode.
	ivpu_mmu_read_imm32_prot:
		jmp ivpu_hardware_interrupt_handler


#Read an immediate for executing a fast branch.
ivpu_mmu_read_branch_addr:
	jmp ivpu_memory_range_fault_handler







#Read a 32  bit instruction immediate (next word) for a memory read operation.
ivpu_mmu_read_inst_imm32_memrd:
	test rsi, 0x2000								#Check to see if we are in protected mode.				
	jnz ivpu_mmu_read_imm32_prot                    #If we are in protected mode, go to the appropriate function.
	mov rax, rdi									#Move the instruction pointer into rax.
	add rax, 0x4									#Add 4 to the instruction pointer (second word address).
	cmp r12, rax									#Compare the pointer in rax to the memory size in r12.
	jl ivpu_memory_range_fault_handler				#If the calculated address is out of memory bounds, trigger a memory fault.
	mov rbx, 0x0									#Zero out rbx.
	mov ebx, [r13 + rax]							#Move the value in word 2 into ebx.
	jmp ivpu_imm32_memrd_ret						#Return to the memory read function.


ivpu_mmu_read_inst_imm32_memrd2:
	test rsi, 0x2000								#Check to see if we are in protected mode.				
	jnz ivpu_mmu_read_imm32_prot                    #If we are in protected mode, go to the appropriate function.
	mov rax, rdi									#Move the instruction pointer into rax.
	add rax, 0x4									#Add 4 to the instruction pointer (second word address).
	cmp r12, rax									#Compare the pointer in rax to the memory size in r12.
	jl ivpu_memory_range_fault_handler				#If the calculated address is out of memory bounds, trigger a memory fault.
	mov rbx, 0x0									#Zero out rbx.
	mov ebx, [r13 + rax]							#Move the value in word 2 into ebx.
	jmp ivpu_imm32_memrd2_ret						#Return to the memory read function.













#Perform a memory read (memory address is in the second word of the instruction, rbx).
ivpu_mmu_read_dat32:
	test rsi, 0x2000								#Check to see if we are in protected mode.
	jnz ivpu_mmu_read_dat32_prot					#If we are in protected mode, go to the appropriate function.
	cmp r12, rbx									#Compare the address in rbx to the memory size in r12.
	jl ivpu_memory_range_fault_handler				#If the address is out of memory bounds, trigger a memory fault.
	mov rcx, 0x0									#Zero out rcx.
	mov ecx, [r13 + rbx]							#Move the value in the designated memory address into ecx (read 1).
	jmp ivpu_execute

	ivpu_mmu_read_dat32_prot:
		jmp hardwareInt


#Perform a memory read (memory address is presented as offset utilizing the r0 regsiter, and the value in the second word of the instruction, rbx).
ivpu_mmu_read_offset32:
	test rsi, 0x2000								#Check to see if we are in protected mode.
#	jnz ivpu_mmu_read_offset32_prot					#If we are in protected mode, go to the appropriate function.
	mov rax, 0x0									#Zero out rax.
	mov rax, [r14 + 2080 + rdx]						#Get the value in the offset register, and store it in ebx.
	
	mov rdx, 0x3FFFFFFF								#Create a mask for the immediate value in the offset.
	and rdx, rbx									#Get the immediate value by applying the offset immediate mask. Store it in rdx.

	mov rcx, 0x40000000								#Create a mask for operation bit in the offset (bit 30).
	and rcx, rbx									#Get the operational bit.									#Get the immediate value in the offset.
	cmp rcx, 0x0									#Check the operation bit by comparing it to zero.

	je ivpu_mmu_read_offset32_add                   #If the operation bit has not been set (thus, ecx is zero), then we add the offset immediate to the offset register value.
	jmp ivpu_mmu_read_offset32_sub                  #If the operation bit has been set (thus, ecx is not zero), then we subtract the offset immediate from the offset register value.

	ivpu_mmu_read_offset32_add:
		add rax, rdx								#Add the offset. The memory address is now in rbx.
		mov rdx, rax								#Move rax into rdx.
		cmp r12, rdx								#Compare the address in rbx to the memory size in r12.
		jl ivpu_memory_range_fault_handler			#If the address is out of memory bounds, trigger a memory fault.
		mov rbx, 0x0								#Zero out rbx.
		mov ecx, [r13 + rdx]						#Move the value in the designated memory address into ebx.
		jmp ivpu_execute							#Execute the opcode.


	ivpu_mmu_read_offset32_sub:
		sub rax, rdx								#Subtract the offset. The memory address is now in rbx.
		mov rdx, rax								#Move the memory address into rdx.
		cmp r12, rdx								#Compare the address in rbx to the memory size in r12.
		jl ivpu_memory_range_fault_handler			#If the address is out of memory bounds, trigger a memory fault.
		mov rbx, 0x0								#Zero out rbx.
		mov ecx, [r13 + rdx]						#Move the value in the designated memory address into ebx.
		jmp ivpu_execute							#Execute the opcode.


#Perform a memory read (memory address is presented in the offset register (r0)).
ivpu_mmu_read_reg32:
	test rsi, 0x2000								#Check to see if we are in protected mode.
#	jnz ivpu_mmu_read_offset32_prot					#If we are in protected mode, go to the appropriate function.
	mov rax, 0x0									#Zero out rax.
	mov rax, [r14 + 2080 + rdx]						#Get the value in the offset register, and store it in ebx.
	cmp r12, rax									#Compare the address in rbx to the memory size in r12.
	jl ivpu_memory_range_fault_handler				#If the address is out of memory bounds, trigger a memory fault.
	mov rcx, 0x0									#Zero out rbx.
	mov ecx, [r13 + rax]							#Move the value in the designated memory address into ebx.
	jmp ivpu_execute								#Execute the opcode.





#Perform an address computation (memory address is presented as offset utilizing the r0 regsiter, and the value in the second word of the instruction, rdx).
ivpu_mmu_compaddr_dat32:
	test rsi, 0x2000								#Check to see if we are in protected mode.
	jnz ivpu_mmu_compaddr_dat32_prot				#If we are in protected mode, go to the appropriate function.
	cmp r12, rbx									#Compare the address in rbx to the memory size in r12.
	jl ivpu_memory_range_fault_handler				#If the address is out of memory bounds, trigger a memory fault.
	jmp ivpu_execute

	ivpu_mmu_compaddr_dat32_prot:
		jmp hardwareInt


ivpu_mmu_compaddr_offset32:
	test rsi, 0x2000								#Check to see if we are in protected mode.
#	jnz ivpu_mmu_read_offset32_prot					#If we are in protected mode, go to the appropriate function.
	mov rax, 0x0									#Zero out rbx.
	mov rax, [r14 + 2080 + rdx]						#Get the value in the offset register, and store it in rcx.

	mov rdx, 0x3FFFFFFF								#Create a mask for the immediate value in the offset.
	and rdx, rbx									#Get the immediate value by applying the offset immediate mask. Store it in rax.
	
	mov r11, 0x40000000								#Create a mask for operation bit in the offset (bit 30).
	and r11, rbx									#Get the operational bit.									#Get the immediate value in the offset.
	cmp r11, 0x0									#Check the operation bit by comparing it to zero.
	
	je ivpu_mmu_compaddr_offset32_add               #If the operation bit has not been set (thus, ecx is zero), then we add the offset immediate to the offset register value.
	jmp ivpu_mmu_compaddr_offset32_sub              #If the operation bit has been set (thus, ecx is not zero), then we subtract the offset immediate from the offset register value.

	ivpu_mmu_compaddr_offset32_add:
		add rax, rdx								#Add the offset. The memory address is now in rbx.
		mov rbx, rax								#Move the memory address into rdx.
		cmp r12, rbx								#Compare the address in rbx to the memory size in r12.
		jl ivpu_memory_range_fault_handler			#If the address is out of memory bounds, trigger a memory fault.
		jmp ivpu_execute							#Execute the opcode.


	ivpu_mmu_compaddr_offset32_sub:
		sub rax, rdx								#Add the offset. The memory address is now in rbx.
		mov rbx, rax								#Move the memory address into rdx.
		cmp r12, rbx								#Compare the address in rbx to the memory size in r12.
		jl ivpu_memory_range_fault_handler			#If the address is out of memory bounds, trigger a memory fault.
		jmp ivpu_execute							#Execute the opcode.


#Perform a memory read (memory address is presented in the offset register (r0)).
ivpu_mmu_compaddr_reg32:
	test rsi, 0x2000								#Check to see if we are in protected mode.
#	jnz ivpu_mmu_read_reg32_prot					#If we are in protected mode, go to the appropriate function.
	mov rbx, 0x0									#Zero out rdx.
	mov ebx, [r14 + 2080 + rdx]						#Get the value in the offset register, and store it in edx.
	cmp r12, rbx									#Compare the address in rbx to the memory size in r12.
	jl ivpu_memory_range_fault_handler				#If the address is out of memory bounds, trigger a memory fault.
	jmp ivpu_execute								#Execute the opcode.






