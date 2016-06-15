ivpu_execute:
	mov r11, 0xFF000000								#Create an opcode mask.
	and r11, r15									#Pull the opcode from the instruction by using the mask.
	shr r11, 0x15									#Shift the opcode to the right by 21 places in order to get the correct offset into the opcode pointer vector.
	jmp [r14 + r11]									#Jump to the opcode's logic address.
