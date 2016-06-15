ivpu_memory_range_fault_handler:
	mov rsi, qword ptr [r14 + 2056]
	jmp memFault

ivpu_hardware_interrupt_handler:
	mov rsi, qword ptr [r14 + 2056]
	jmp hardwareInt


#Temporary...
ivpu_processInstruction:
	mov rsi, qword ptr [r14 + 2056]
	jmp instProc

ivpu_protectedMode:
	mov rsi, qword ptr [r14 + 2056]
	jmp enterProtMode
	

