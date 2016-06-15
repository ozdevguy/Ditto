
i_vpu_control_decode:				#Instruction located in register rdi, protected mode flag value located in register rbx
	
	#First things first. We need to get the instruction flags.
	mov rax, rdi
	shr rax, 0x10
	cmove rax, qword ptr i_vpu_control_decode



