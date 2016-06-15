
#Fetch, Decode, & Read -> RBX, RCX, RAX, RDX are useable registers.

_fetch:

	#Hardware interrupt check.
	mov rbx, 0x400									#Create a mask for the HI flag in the FLAGS register.
	and rbx, rsi									#Get the HI flag by applying the mask.
	mov rcx, qword ptr [r14 + 2208]					#Move the HWI register from the  VPU vector into rcx.
	test rbx, rcx									#Check to see if both the HI flag and Hardware Interrupt Detected bits are set.
	mov rax, offset _contFetch                      #Move the address of _contFetch into rax
	mov rdx, offset _hardware_interrupt_handler     #Move the address of _hardware_interrupt_handler into rdx
	cmovz rdx, rax									#If the HI flag and Hardware Interrupt Detected bits are not BOTH active, place the _contFetch address into rdx.
	jmp rdx											#Jump to the address in rdx.

_contFetch:											#Continue the instruction fetch process...
	cmp rsp, rdi									#Compare the current instruction pointer to the attached memory size.
	jl _memory_range_fault_handler                  #If the given instruction pointer is out of bounds, trigger a memory range fault.

	test rsi, 0x2000								#Check the PR flag in the FLAGS register.
	jnz _protectedMode                  			#If the PR flag is set, jump to protected mode decoding.
											
_privilegedMode:									#Decode instruction in privileged mode.
	mov r15, qword ptr [r13 + rdi]					#Copy the instruction from memory into the instruction register.

	#Get the instruction architecture.
	mov rcx, 0x100000								#Move the architecture mask into rcx.
	mov r12, r15									#Move the instruction into r12.
	and r12, rcx									#Apply the architecture mask. Only keep the architecture bit.
	shr r12, 0x10									#Shift the architecture bit into its proper place in r12.
	

	#If this is an immediate, unconditional branch, we can skip the decoding process and perform an immediate jump.
	mov rbx, 0x400000								#Create a mask for the jump bit within the instruction.
	test r15, rbx									#Check the instruction's jump bit.
	jne _immediateJump                              #If the instruction's jump bit is set, stop decoding the current instruction and perform an immediate jump.
	

	#Decode the instruction (afterwards, RAX will contain the addressing operation pointer).

_privilegedDecode: 
	
	#Get the instructions addressing mode and move it to bit position 1 in r12.
	mov rax, 0xF0000								#Create a mask for the instruction's addressing mode.
	and rax, r15									#Mask off the instruction's addressing mode.
	shr rax, 0x10									#Move the addressing mode to the right by 16 bits (place it at bit 0).
	or r12, rax										#Apply the instruction format to r12.									
	
	#Prefetch possible write register values.
	mov rax, 0xF000									#Create a mask for write 0.
	and rax, r15									#Get the register address for write 0 from the instruction.
	or r12, rax										#Apply the register address for write 0 to r12

	mov rax, 0xF0									#Create a mask for write 1.
	and rax, r15									#Get the register address for write 1 from the instruction.
	shl rax, 0x4									#Shift the register address left by 4 to get it into the proper position.
	or r12, rax										#Apply the register address for write 1 to r12.
	mov r11, 0x1F									#Create a mask for the first 5 bits of r12.
	and r11, r12									#Move the first 5 bits of r12 into r11.



	#Let's write the register address for read 0 into rax, and the register address for read 1 into rdx.
	mov rax, 0xF00									#Create a mask for read 0.
	and rax, r15									#Get the register address for read 0 using the mask.
	shr rax, 0x8									#Shift the address to the right by 8 bits to bit position 0.

	mov rdx, 0xF									#Create a mask for read 1.
	and rdx, r15									#Get the register address for read 1 using the mask.

	#32 BIT ADDRESSING MODES

	mov rbx, 0x0									#Clear rbx (read 0)
	mov rcx, 0x0									#Clear rcx (read 1)

	cmp r11, 0x0									#Compare the value in r11 to 0 (32 bit, format type 0)
	shl rax, 0x3									#Normalize the read 0 register address.
	cmovz rbx, [r14 + 2080 + rax]					#If this is the correct format, move the value in the register specified for read0 into rbx.
	shl rdx, 0x3									#Normalize the read 1 register address.
	cmovz rcx, [r14 + 2080 + rdx]					#If this is the correct format, move the value in the register specified for read1 into rcx.
	jz _execute										#Execute the opcode

	cmp r11, 0x1									#Compare the value in r11 to 1 (32 bit, format type 1)
	shl rax, 0x3									#Normalize the read 0 register address.
	cmovz rbx, [r14 + 2080 + rax]					#Move the value specified for read 0 into rbx.
	mov rcx, rdx									#The value in rdx is in fact the immediate value we want for read 1.
	jz _execute										#Execute the opcode

	cmp r11, 0x2									#Compare the value in r11 to 2 (32 bit, format type 2)
	shl rax, 0x3									#Normalize the read 0 register address.
	cmovz rbx, [r14 + 2080 + rax]					#If this is format 2, move the value in the register specified for read0 into rbx.
	mov rcx, 0xFF									#Create a mask for one full byte.
	and rcx, r15									#Mask off the first byte of the instruction in order to get our immediate value for read1.
	cmp r11, 0x2
	jz _execute										#Execute the opcode

	cmp r11, 0x3									#Compare the value in r11 to 3 (32 bit, format type 3)
	mov rbx, 0x0									#Move 0 into rbx (no read register)
	mov rcx, 0xFFF									#Create a mask for the first 12 bits of the instruction.
	and rcx, r15									#Apply the mask to the instruction to get our immediate value.
	cmp r11, 0x3
	jz _execute										#Execute the opcode.

	cmp r11, 0x4									#Compare the value in r11 to 4 (32 bit, format type 4)
	mov rbx, 0x0									#Move 0 into rbx (no read register)
	mov rcx, 0xFFFF									#Create a mask for the first 2 bytes of the instruction.
	and rcx, r15									#Apply the mask to the instruction to get our immediate value.
	cmp r11, 0x4
	jz _execute										#Execute the opcode.

	#Skip 0x5 and 0x6 for now (secondary registers)...

	cmp r11, 0x7									#Compare the value in r11 to 7 (32 bit, format type 7).
	shl rax, 0x3									#Normalize the read 0 register address.
	cmovz rbx, [r14 + 2080 + rax]					#Move the value in the register specified in read0 into rbx.
	cmovz ecx, [r13 + rdi + 4]						#Move the immediate value in the second part of the instruction into ecx (since this is a 32 bit instruction, we must use ecx).
	jz _execute                                     #Execute the opcode.

	#Skip 0x8 for now (secondary registers)...

	#MEMORY READ
	cmp r11, 0x9									#Compare the value in r11 to 9 (32 bit, format type 9).
	mov r11, 0x200000								#Create a mask for the instruction's offset bit.
	shl rax, 0x3
	shl rdx, 0x3
	test r11, r15									#Check to see if the offset bit is ticked.
	jnz _mmu_priv_read_compute_offset				#If the offset bit is checked, we need to compute the address and pull the data using the offset calculator.
	jmp _mmu_priv_read_immediate					#If the offset bit is not checked, we use the data in the second word as an address and pull the data using the standard memory reader.




_mmu_priv_read_immediate:
	mov r11d, [r13 + rdi + 4]						#Move the memory address in the second word of the instruction into rll.
	cmp rsp, r11									#Check to ensure this memory address falls within the current memory range.
	jl _memory_range_fault_handler                  #If the address in r11 is out of bounds, trigger a memory range fault.
	mov rbx, 0x0									#If the address in r11 is valid, place 0 in read 0.
	mov ecx, [r11]									#Place the data at the address in r11 into read 1.
	jmp _execute           							#Execute the opcode.                        

_mmu_priv_read_compute_offset:
	mov r11d, [r13 + rdi + 4]						#Move the offset in the second word of the instruction into r11.
	mov ecx, 0xE0000000								#Create a mask for the Ru and Off1 fields.
	and ecx, [r13 + rdi + 4]						#NOT COMPLETE
	shr ecx, 29
	jmp _execute
	





_execute:											#Execute the operation specified in the opcode.
	mov r11, 0xFF000000								#Create an opcode mask.
	and r11, r15									#Pull the opcode from the instruction by using the mask.
	shr r11, 0x15									#Shift the opcode to the right by 21 places in order to get the correct offset into the opcode pointer vector.
	jmp _processInstruction
	jmp [r14 + r11]									#Jump to the opcode.



_regWriteBack:
	mov rcx, r12
	and rcx, 0xF000
	shr rcx, 0x9
	mov [r14 + 2088], rax
	jmp _protectedMode




_immediateJump:
	test r12, 0x10									#Check the architecture of the current instruction.
	cmovz ebx, dword ptr [r13 + rdi + 4]			#If the result of the check is 0, then this is a 32 bit instruction. As such, the instruction is only 4 bytes, se we use ebx to move the address in instruction part 2.
	cmovnz rbx, qword ptr [r13 + rdi + 8]			#If the result of the check is 1, then this is a 64 bit instruction, which is a full 8 bytes. We use ebx to move the address in instruction part 2.
	mov rdi, rbx
	jmp _fetch



_immJmpRet:
	jmp _fetch

_processInstruction:
	mov rsi, qword ptr [r14 + 2056]
	jmp instProc

_protectedMode:
	mov rsi, qword ptr [r14 + 2056]
	jmp enterProtMode
	

_hardware_interrupt_handler:
	mov rsi, qword ptr [r14 + 2056]
	jmp hardwareInt

_memory_range_fault_handler:
	mov rsi, qword ptr [r14 + 2056]
	jmp memFault
		







