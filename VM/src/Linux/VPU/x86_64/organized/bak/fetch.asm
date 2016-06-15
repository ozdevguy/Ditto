
ivpu_fetch:

	#Hardware interrupt check.
	mov rbx, 0x400										#Create a mask for the HI flag in the FLAGS register.
	and rbx, rsi										#Get the HI flag by applying the mask.
	mov rcx, qword ptr [r14 + 2208]						#Move the HWI register from the  VPU vector into rcx.
	test rbx, rcx										#Check to see if both the HI flag and Hardware Interrupt Detected bits are set.
	mov rax, offset ivpu_fetch_cont                  	#Move the address of ivpu_fetch_cont into rax
	mov rdx, offset ivpu_hardware_interrupt_handler     #Move the address of _hardware_interrupt_handler into rdx
	cmovz rdx, rax										#If the HI flag and Hardware Interrupt Detected bits are not BOTH active, place the _contFetch address into rdx.
	jmp rdx												#Jump to the address in rdx.

ivpu_fetch_cont:										#Continue the instruction fetch process...

	cmp rsp, rdi										#Compare the current instruction pointer to the attached memory size.
	jl ivpu_memory_range_fault_handler                  #If the given instruction pointer is out of bounds, trigger a memory range fault.

	test rsi, 0x2000									#Check the PR flag in the FLAGS register.
	jnz ivpu_decode_protected                  			#If the PR flag is set, jump to protected mode decoding.
	jmp ivpu_decode_privileged

