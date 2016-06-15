ivpu_immediateJump:
	test r12, 0x10									#Check the architecture of the current instruction.
	cmovz ebx, dword ptr [r13 + rdi + 4]			#If the result of the check is 0, then this is a 32 bit instruction. As such, the instruction is only 4 bytes, se we use ebx to move the address in instruction part 2.
	cmovnz rbx, qword ptr [r13 + rdi + 8]			#If the result of the check is 1, then this is a 64 bit instruction, which is a full 8 bytes. We use ebx to move the address in instruction part 2.
	mov rdi, rbx
	jmp ivpu_fetch
	