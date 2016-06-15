
#Read instructions.

#Immediate in second word. (Read Register Address 0: rax, Read Register Address 1: rdx | Read Line 0: rbx, Read Line 1: rcx)

ivpu_read_32_0:										#IP + 4 = |-----------------Immediate--------------------|
													#IP =     |--Opcode--|--Flags--| Wr1 | R1 | Wr0 | Unused |												
	mov rcx, 0xFE3FFFFF								#Create an instruction layout flag mask (32 bit, single word instruction).
	and rsi, rcx									#Apply the instruction layout flags to the FLAGS register (bits 22, 23, and 24).
	mov rcx, 0x800000								#Create a mask for bit 23, to signal that this 32 bit instruction is composed of two words.
	or rsi, rcx										#Apply bit 23 to the FLAGS register.
	mov rcx, 0x0									#Zero out rcx.
	mov rbx, 0x0									#Zero out rbx.
	mov ecx, dword ptr [r14 + rdx + 2080]			#Move the value in the given register for read 1 into ecx.
	jmp ivpu_mmu_read_inst_imm32					#Read the immediate value in the next word.


#Skip 2 for now (special registers).
	

#Addressing with registers ONLY.					
ivpu_read_32_4:										#|--Opcode--|--Flags--| Wr1 | R1 | Wr0 | R0 |
	
	mov rcx, 0xFE3FFFFF								#Create an instruction layout flag mask (32 bit, single word instruction).
	and rsi, rcx									#Apply the instruction layout flags to the FLAGS register (bits 22, 23, and 24).
	mov rcx, 0x0									#Zero out rcx.
	mov rbx, 0x0									#Zero out rbx.
	mov ebx, dword ptr [r14 + rax + 2080]			#Move the value in the given register for read 0 into ebx.
	mov ecx, dword ptr [r14 + rdx + 2080]			#Move the value in the given register for read 1 into ecx.
	jmp ivpu_execute								#Execute

#Skip 5 and 6 for now (special registers).
#7 is unused.

#Addressing with Register and Immediate in single word.

ivpu_read_32_8:										#|--Opcode--|--Flags--| Wr1 | R1 | Wr0 | Imm |

	mov rcx, 0xFE3FFFFF								#Create an instruction layout flag mask (32 bit, single word instruction).
	and rsi, rcx									#Apply the instruction layout flags to the FLAGS register (bits 22, 23, and 24).
	mov rcx, 0x0									#Zero out rcx.
	mov rbx, 0x0									#Zero out rbx.
	mov ecx, dword ptr [r14 + rdx + 2080]			#Move the value in the given register for read 1 into ecx.
	shr eax, 0x3									#Shift eax to the right by 3 places.
	mov ebx, eax									#The value in edx is the actual immediate value we're looking for. Move it into ecx.
	jmp ivpu_execute								#Execute

ivpu_read_32_10:									#|--Opcode--|--Flags--| Wr1 | R1 |   Imm   |

	mov rcx, 0xFE3FFFFF								#Create an instruction layout flag mask (32 bit, single word instruction).
	and rsi, rcx									#Apply the instruction layout flags to the FLAGS register (bits 22, 23, and 24).
	mov rcx, 0x0									#Zero out rcx.
	mov rbx, 0x0									#Zero out rbx.
	mov ecx, dword ptr [r14 + rdx + 2080]			#Move the value in the given register for read 1 into ecx.
	mov rdx, 0xFF									#Move a mask for the first byte into rdx.
	and rdx, r15									#Get the immediate value by applying the mask.
	mov rbx, rdx									#Move the immediate value into ebx (read 0). 
	jmp ivpu_execute								#Execute.

ivpu_read_32_12:									#|--Opcode--|--Flags--| Wr1 | Imm |   Imm   |

	mov rcx, 0xFE3FFFFF								#Create an instruction layout flag mask (32 bit, single word instruction).
	and rsi, rcx									#Apply the instruction layout flags to the FLAGS register (bits 22, 23, and 24).
	mov rcx, 0x0									#Zero out rcx.
	mov rbx, 0x0									#Zero out rbx.
	mov rax, 0xFFF									#Move a mask for the first twelve bits into rax.
	and rax, r15									#Get the immediate value by applying the mask.
	mov ebx, eax									#Move the immediate value into ebx.
	jmp ivpu_execute								#Execute

ivpu_read_32_14:									#|--Opcode--|--Flags--|   Imm   |   Imm   |
	
	mov rcx, 0xFE3FFFFF								#Create an instruction layout flag mask (32 bit, single word instruction).
	and rsi, rcx									#Apply the instruction layout flags to the FLAGS register (bits 22, 23, and 24).
	mov rcx, 0x0									#Zero out rcx.
	mov rbx, 0x0									#Zero out rbx.
	mov rax, 0xFFFF									#Move a mask for the first two bytes into rax.
	and rax, r15									#Get the immediate value by applying the mask.
	mov ebx, eax									#Move the immediate value into ecx.
	jmp ivpu_execute								#Execute

#Memory addressing.

#Read from memory.

ivpu_read_32_9:
	mov rax, 0xFE3FFFFF								#Create an instruction layout flag mask (32 bit, single word instruction).
	and rsi, rax									#Apply the instruction layout flags to the FLAGS register (bits 22, 23, and 24).
	mov rax, 0x800000								#Create a mask for bit 23, to signal that this 32 bit instruction is composed of two words.
	or rsi, rax										#Apply bit 23 to the FLAGS register.
	jmp ivpu_mmu_read_inst_imm32_memrd				#Get the second word of the instruction (the offset/full immediate address).

ivpu_imm32_memrd_ret:								#Return from getting the second word of the instruction. The word will be in ebx.
	mov rax, 0xFFDFFFFF								#Create a mask to clear the old offset stow bit.
	and rsi, rax									#Clear the old offset stow bit.
	mov rax, 0x200000								#Create a mask for the offset bit in the instruction (bit 21).
	and rax, r15									#Pull the offset bit by applying the mask to the instruction.
	or rsi, rax										#Apply the offset bit to bit 21 of the FLAGS register in order to safely stow away the bit.
	mov rax, 0x80000000								#Create a mask for the Ru bit in the second word.
	and rax, rbx									#Apply the mask to pull the Ru bit.
	shr rax, 0xB									#Shift the Ru bit to the right by 11 places.
	or rax, rsi										#Add the offset bit (and the rest of the FLAGS register) by using the OR operator.						
	shr rax, 0x14									#Get rid of the rest of the FLAGS register, and move our desired value to bit position 0.
	and rax, 0x3									#Make sure we kill all bits after bit 1.
	cmp rax, 0x2									#Compare the value in rcx to 2 in order to decide how the memory address is presented (00, 10, or 11).
	jl ivpu_mmu_read_dat32							#If the value in rcx is less than 1 (00), then there exists an immediate memory address in word 2.
	je ivpu_mmu_read_offset32						#If the value in rcx is equal to 1, the memory address is presented as an offset to be computed.
	jg ivpu_mmu_read_reg32							#If the value in rcx is greater than 1 (11), the memory address is actually in the offset register.


#Write to memory.

ivpu_read_32_11:
	mov ecx, dword ptr [r14 + rax + 2080]			#Get the value in the read 0 register, and place it on read 0.
	mov rax, 0xFE3FFFFF								#Create an instruction layout flag mask (32 bit, single word instruction).
	and rsi, rax									#Apply the instruction layout flags to the FLAGS register (bits 22, 23, and 24).
	mov rax, 0x800000								#Create a mask for bit 23, to signal that this 32 bit instruction is composed of two words.
	or rsi, rax										#Apply bit 23 to the FLAGS register.
	jmp ivpu_mmu_read_inst_imm32_memrd2				#Get the second word of the instruction (the offset/full immediate address).

	ivpu_imm32_memrd2_ret:								#Return from getting the second word of the instruction. The word will be in ebx.
		mov rax, 0xFFDFFFFF								#Create a mask to clear the old offset stow bit.
		and rsi, rax									#Clear the old offset stow bit.
		mov rax, 0x200000								#Create a mask for the offset bit in the instruction (bit 21).
		and rax, r15									#Pull the offset bit by applying the mask to the instruction.
		or rsi, rax										#Apply the offset bit to bit 21 of the FLAGS register in order to safely stow away the bit.
		mov rax, 0x80000000								#Create a mask for the Ru bit in the second word.
		and rax, rbx									#Apply the mask to pull the Ru bit.
		shr rax, 0xB									#Shift the Ru bit to the right by 11 places.
		or rax, rsi										#Add the offset bit (and the rest of the FLAGS register) by using the OR operator.						
		shr rax, 0x14									#Get rid of the rest of the FLAGS register, and move our desired value to bit position 0.
		and rax, 0x3									#Make sure we kill all bits after bit 1.
		cmp rax, 0x2									#Compare the value in rcx to 2 in order to decide how the memory address is presented (00, 10, or 11).
		jl ivpu_mmu_compaddr_dat32						#If the value in rcx is less than 1 (00), then there exists an immediate memory address in word 2.
		je ivpu_mmu_compaddr_offset32					#If the value in rcx is equal to 1, the memory address is presented as an offset to be computed.
		jg ivpu_mmu_compaddr_reg32						#If the value in rcx is greater than 1 (11), the memory address is actually in the offset register.


															
	



	



