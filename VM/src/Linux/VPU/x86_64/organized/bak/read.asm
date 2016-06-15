
ivpu_read:
	mov rbx, 0x0									#Clear rbx (read 0)
	mov rcx, 0x0									#Clear rcx (read 1)

	cmp r11, 0x0									#Compare the value in r11 to 0 (32 bit, format type 0)
	shl rax, 0x3									#Normalize the read 0 register address.
	cmovz rbx, [r14 + 2080 + rax]					#If this is the correct format, move the value in the register specified for read0 into rbx.
	shl rdx, 0x3									#Normalize the read 1 register address.
	cmovz rcx, [r14 + 2080 + rdx]					#If this is the correct format, move the value in the register specified for read1 into rcx.
	jz ivpu_execute									#Execute the opcode

	cmp r11, 0x1									#Compare the value in r11 to 1 (32 bit, format type 1)
	shl rax, 0x3									#Normalize the read 0 register address.
	cmovz rbx, [r14 + 2080 + rax]					#Move the value specified for read 0 into rbx.
	mov rcx, rdx									#The value in rdx is in fact the immediate value we want for read 1.
	jz ivpu_execute									#Execute the opcode

	cmp r11, 0x2									#Compare the value in r11 to 2 (32 bit, format type 2)
	shl rax, 0x3									#Normalize the read 0 register address.
	cmovz rbx, [r14 + 2080 + rax]					#If this is format 2, move the value in the register specified for read0 into rbx.
	mov rcx, 0xFF									#Create a mask for one full byte.
	and rcx, r15									#Mask off the first byte of the instruction in order to get our immediate value for read1.
	cmp r11, 0x2
	jz ivpu_execute									#Execute the opcode

	cmp r11, 0x3									#Compare the value in r11 to 3 (32 bit, format type 3)
	mov rbx, 0x0									#Move 0 into rbx (no read register)
	mov rcx, 0xFFF									#Create a mask for the first 12 bits of the instruction.
	and rcx, r15									#Apply the mask to the instruction to get our immediate value.
	cmp r11, 0x3
	jz ivpu_execute									#Execute the opcode.

	cmp r11, 0x4									#Compare the value in r11 to 4 (32 bit, format type 4)
	mov rbx, 0x0									#Move 0 into rbx (no read register)
	mov rcx, 0xFFFF									#Create a mask for the first 2 bytes of the instruction.
	and rcx, r15									#Apply the mask to the instruction to get our immediate value.
	cmp r11, 0x4
	jz ivpu_execute									#Execute the opcode.

	#Skip 0x5 and 0x6 for now (secondary registers)...

	cmp r11, 0x7									#Compare the value in r11 to 7 (32 bit, format type 7).
	shl rax, 0x3									#Normalize the read 0 register address.
	cmovz rbx, [r14 + 2080 + rax]					#Move the value in the register specified in read0 into rbx.
	cmovz ecx, [r13 + rdi + 4]						#Move the immediate value in the second part of the instruction into ecx (since this is a 32 bit instruction, we must use ecx).
	jz ivpu_execute                                 #Execute the opcode.

	#Skip 0x8 for now (secondary registers)...

	#MEMORY READ

	cmp r11, 0x9									#Compare the value in r11 to 9 (32 bit, format type 9).
	mov r11, 0x200000								#Create a mask for the instruction's offset bit.
	shl rax, 0x3
	shl rdx, 0x3
	test r11, r15									#Check to see if the offset bit is ticked.
	jnz ivpu_mmu_priv_read_compute_offset_32		#If the offset bit is checked, we need to compute the address and pull the data using the offset calculator.
	jmp ivpu_mmu_priv_read_immediate_32				#If the offset bit is not checked, we use the data in the second word as an address and pull the data using the standard memory reader.
