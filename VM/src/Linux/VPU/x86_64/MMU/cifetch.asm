#The Ditto Virtual Machine
#=========================
#Virtual Processing Unit
#Check to make sure the requested instruction address is accessible.


#Prepare instruction fetch.

i_vpu_mmu_fetch_next_i:					
	mov rax, offset i_vpu_mmu_fetch_next_i_r1		#Setup PR flag get function.
	jmp i_vpu_flags_pr_g							#Get the PR flag.

i_vpu_mmu_fetch_next_i_r1:
	mov rbx, rdx									#Store the protected mode flag in rbx for future fast access when parsing the opcode.
	shl rdx, 0x3									#If the protected mode value is 1, change the value to 8
	add rdx, 0x828									#Add 0x828 to the value of rdx (either 0 or 8) in order to get the correct mmu fetch operation (privileged or protected).

	#We should now know if protected mode is enabled or not. Jump to the appropriate MMU function to fetch the instruction.
	jmp [r14 + rdx]


#Fetch the next instruction in privileged mode (any address works, as long as it is within range).
i_vpu_mmu_fetch_next_i_priv:
	mov rax, qword ptr [r14 + 2080]					#Get the instruction pointer.
	mov rcx, qword ptr [2048]						#Get the currently attached memory size.
	cmp rcx, rax									#Check the instruction pointer to ensure that it lies within available memory.
	nop
	jge i_vpu_mmu_fetch_next_i_mem_outofbounds		#If the instruction pointer is out of range of the currently attached memory, call the out of bounds interrupt.
	add rax, r13									#Add the instruction pointer to the attached memory pointer to get the correct system memory address.
	mov rdi, qword ptr [rax]						#Move the instruction into the instruction pointer.				
	jmp i_vpu_control_decode						#Jump to control unit decoder | Decode the instruction.


#Fetch the next instruction in protected mode (use Virtual Memory).
i_vpu_mmu_fetch_next_i_prot:
	jmp protMemCalled

i_vpu_mmu_fetch_next_i_mem_outofbounds:
	jmp memOutOfBounds
