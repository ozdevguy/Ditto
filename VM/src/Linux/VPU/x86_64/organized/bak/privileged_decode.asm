
ivpu_decode_privileged:
	mov r15, qword ptr [r13 + rdi]					#Copy the instruction from memory into the instruction register.

	#Get the instruction architecture.
	mov rcx, 0x100000								#Move the architecture mask into rcx.
	mov r12, r15									#Move the instruction into r12.
	and r12, rcx									#Apply the architecture mask. Only keep the architecture bit.
	shr r12, 0x10									#Shift the architecture bit into its proper place in r12.
	
	#If this is an immediate, unconditional branch, we can skip the decoding process and perform an immediate jump.
	mov rbx, 0x400000								#Create a mask for the jump bit within the instruction.
	test r15, rbx									#Check the instruction's jump bit.
	jne ivpu_immediateJump                          #If the instruction's jump bit is set, stop decoding the current instruction and perform an immediate jump.
	
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
	jmp ivpu_read									#Now that we've decode the instruction, we need to read in any specified data.
	