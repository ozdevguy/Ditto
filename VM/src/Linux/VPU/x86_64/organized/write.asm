ivpu_register_writeback_null:
	mov rax, rsi									#Copy the FLAGS register into rax.
	shr rax, 0x16									#Shift the FLAGS register right by 22 in order to get the instruction layout bits.
	cmp rax, 0x0									#Compare the value in RAX to 0.
	je ivpu_adjust_ip_4								#If the value in RAX is 0, increment the instruction pointer by 4.
	cmp rax, 0x2									#Compare the value in rax to 2
	je ivpu_adjust_ip_8								#If the value in RAX is 2, increment the instruction pointer by 8.
	cmp rax, 0x1									#Compare the value in rax to 1.
	je ivpu_adjust_ip_8								#If the value in RAX is 1, increment the instruction pointer by 8.
	cmp rax, 0x3									#Compare the value in rax to 3.
	je ivpu_adjust_ip_16							#If the value in RAX is 3, increment the instruction pointer by 16.


ivpu_register_writeback_w0:
	mov rbx, 0xF000									#Create a mask for the write 0 register in the instruction.
	and rbx, r15									#Get the write 0 register address by applying the mask to the instruction register.
	shr rbx, 0x9									#Shift the address register to bit position 3.
	mov qword ptr [r14 + rbx + 2080], rax			#Move the value in rax (write 0 line) into the designated register.
	mov rax, rsi									#Copy the FLAGS register into rax.
	shr rax, 0x16									#Shift the FLAGS register right by 22 in order to get the instruction layout bits.
	cmp rax, 0x0									#Compare the value in RAX to 0.
	je ivpu_adjust_ip_4								#If the value in RAX is 0, increment the instruction pointer by 4.
	cmp rax, 0x2									#Compare the value in rax to 2
	je ivpu_adjust_ip_8								#If the value in RAX is 2, increment the instruction pointer by 8.
	cmp rax, 0x1									#Compare the value in rax to 1.
	je ivpu_adjust_ip_8								#If the value in RAX is 1, increment the instruction pointer by 8.
	cmp rax, 0x3									#Compare the value in rax to 3.
	je ivpu_adjust_ip_16							#If the value in RAX is 3, increment the instruction pointer by 16. 

ivpu_register_writeback_w0w1:
	mov rbx, 0xF000									#Create a mask for the write 0 register in the instruction.
	and rbx, r15									#Get the write 0 register address by applying the mask to the instruction register.
	shr rbx, 0x9									#Shift the address register to bit position 3 in order to normalize the register address.
	mov qword ptr [r14 + rbx + 2080], rax			#Move the value in rax (write 0 line) into the designated register.
	mov rbx, 0xF0									#Create a mask for the write 1 register in the instruction.
	and rbx, r15									#Get the write 1 register address by applying the mask to the instruction pointer.
	shr rbx, 0x1									#Shfit the address register to bit position 3 in order to normalize the register address.
	mov qword ptr [r14 + rbx + 2080], rdx			#Move the value in rdx (write 1 line) into the designated register.
	mov rax, rsi									#Copy the FLAGS register into rax.
	shr rax, 0x16									#Shift the FLAGS register right by 22 in order to get the instruction layout bits.
	cmp rax, 0x0									#Compare the value in RAX to 0.
	je ivpu_adjust_ip_4								#If the value in RAX is 0, increment the instruction pointer by 4.
	cmp rax, 0x2									#Compare the value in rax to 2
	je ivpu_adjust_ip_8								#If the value in RAX is 2, increment the instruction pointer by 8.
	cmp rax, 0x1									#Compare the value in rax to 1.
	je ivpu_adjust_ip_8								#If the value in RAX is 1, increment the instruction pointer by 8.
	cmp rax, 0x3									#Compare the value in rax to 3.
	je ivpu_adjust_ip_16							#If the value in RAX is 3, increment the instruction pointer by 16.



ivpu_adjust_ip_4:
	add rdi, 0x4									#Add 4 to the instruction pointer.
	jmp ivpu_fetch									#Restart the fetch process.

ivpu_adjust_ip_8:
	add rdi, 0x8									#Add 8 to the instruction pointer.						
	jmp ivpu_fetch									#Restart the fetch process.

ivpu_adjust_ip_16:
	add rdi, 0x10									#Add 16 to the instruction pointer.
	jmp ivpu_fetch									#Restart the fetch process.
