

#Decode the instruction.

ivpu_decoder_dispatch:
	
	#If this is an immediate, unconditional branch, we can skip the decoding process and perform an immediate jump.
	mov rbx, 0x400000								#Create a mask for the jump bit within the instruction.
	test r15, rbx									#Check the instruction's jump bit.
	jne ivpu_immediateJump                          #If the instruction's jump bit is set, stop decoding the current instruction and perform an immediate jump.									

	#Since rax and rdx are the write back buffers, and we don't need them yet, let's write the register address for read 0 into rax, and the register address for read 1 into rdx.
	mov rax, 0xF									#Create a mask for read 0.
	and rax, r15									#Get the register address for read 0 using the mask.
	shl rax, 0x3									#Shift the address to the right by 5 bits to bit position 2 (in order to preserve addressing).

	mov rdx, 0xF00									#Create a mask for read 1.
	and rdx, r15									#Get the register address for read 1 using the mask.
	shr rdx, 0x5									#Shift the address to the left by 3 to bit position 2 (in order to preserve addressing).

	mov rbx, 0x1F0000								#Create a mask for the addressing mode and store it in rbx.
	and rbx, r15									#Pull the addressing mode from the instruction.
	shr rbx, 0xD									#Shift the addressing mode to bit positon 0.
	
	mov rcx, 0x0									#Clear rcx (read 1)

	jmp [r14 + rbx + 2208]							#Jump to the correct read function.
	
	