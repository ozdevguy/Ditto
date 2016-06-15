ivpu_mmu_priv_read_compute_offset_32:
	mov r11d, [r13 + rdi + 4]						#Move the offset in the second word of the instruction into r11.
	mov ecx, 0xE0000000								#Create a mask for the offset fields.
	and ecx, r11d									#Apply the mask to the second word.


ivpu_mmu_priv_read_immediate_32:
	mov r11d, [r13 + rdi + 4]						#Move the memory address in the second word of the instruction into rll.
	cmp rsp, r11									#Check to ensure this memory address falls within the current memory range.
	jl ivpu_memory_range_fault_handler              #If the address in r11 is out of bounds, trigger a memory range fault.
	mov rbx, 0x0									#If the address in r11 is valid, place 0 in read 0.
	mov ecx, [r11]									#Place the data at the address in r11 into read 1.
	jmp ivpu_execute           						#Execute the opcode.


ivpu_calc_offset_0_32:
	mov ecx, 0x0
	shr eax
	mov r11d, [r13 + 2080 + rax]
	add ecx, r11d
	mov r11, r15
	

