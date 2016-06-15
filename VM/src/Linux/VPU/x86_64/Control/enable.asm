
.global _vpu_initialize
.global _vpu_start


#Called from C functions.

protMemCalled:
	mov rsp, qword ptr [r14 + 2056]
	push r14
	mov rax, 4
	mov rbx, 1
	mov rcx, offset p1msg
	mov rdx, 18
	int 0x80
	pop r14
	jmp [r14 + 2072]


privMemCalled:
	mov rsp, qword ptr [r14 + 2056]
	push r14
	mov rax, 4
	mov rbx, 1
	mov rcx, offset p2msg
	mov rdx, 18
	int 0x80
	pop r14
	jmp [r14 + 2072]

IPtest:
	mov rsp, qword ptr [r14 + 2056]
	push r14
	mov rax, 4
	mov rbx, 1
	mov rcx, offset p3msg
	mov rdx, 18
	int 0x80
	pop r14
	jmp [r14 + 2072]

memOutOfBounds:
	mov rsp, qword ptr [r14 + 2056]
	push r14
	mov rax, 4
	mov rbx, 1
	mov rcx, offset p4msg
	mov rdx, 18
	int 0x80
	pop r14
	jmp [r14 + 2072]

enterProtMode:
	mov rsp, qword ptr [r14 + 2056]
	push r14
	mov rax, 4
	mov rbx, 1
	mov rcx, offset p5msg
	mov rdx, 18
	int 0x80
	pop r14
	jmp [r14 + 2072]

memFault:
	mov rsp, qword ptr [r14 + 2056]
	push r14
	mov rax, 4
	mov rbx, 1
	mov rcx, offset p6msg
	mov rdx, 18
	int 0x80
	pop r14
	jmp [r14 + 2072]

hardwareInt:
	mov rsp, qword ptr [r14 + 2056]
	push r14
	mov rax, 4
	mov rbx, 1
	mov rcx, offset p7msg
	mov rdx, 18
	int 0x80
	pop r14
	jmp [r14 + 2072]

instProc:
	mov rsp, qword ptr [r14 + 2056]
	push r14
	mov rax, 4
	mov rbx, 1
	mov rcx, offset p8msg
	mov rdx, 18
	int 0x80
	pop r14
	jmp [r14 + 2072]


	
_vpu_initialize: 								#Initialize the VPU Vector (setup opcode mappings).
	pop rax		 								#Pop the C function return address from the stack, store it in rax
	mov rcx, rdi								#Copy the VPU vector pointer into rcx for safe keeping.

	#--BEGIN MAPPING READ POINTERS-->
	add rdi, 2208
	mov qword ptr [rdi], offset ivpu_read_32_0
	add rdi, 32
	mov qword ptr [rdi], offset ivpu_read_32_4
	add rdi, 32
	mov qword ptr [rdi], offset ivpu_read_32_8
	add rdi, 8
	mov qword ptr [rdi], offset ivpu_read_32_9
	add rdi, 8
	mov qword ptr [rdi], offset ivpu_read_32_10
	add rdi, 8
	mov qword ptr [rdi], offset ivpu_read_32_11
	add rdi, 8
	mov qword ptr [rdi], offset ivpu_read_32_12
	add rdi, 16
	mov qword ptr [rdi], offset ivpu_read_32_14

	#--BEGIN MAPPING OPCODES-->

	mov rdi, rcx

	#DTU
	mov qword ptr [rdi], offset __ld 						#ld opcode, 0x0
	add rdi, 8
	mov qword ptr [rdi], offset __str						#str opcode, 0x1
	add rdi, 8
	mov qword ptr [rdi], offset __push						#push opcode, 0x2
	add rdi, 8
	mov qword ptr [rdi], offset __pop						#pop opcode, 0x3
	add rdi, 8
	mov qword ptr [rdi], offset __mov						
	add rdi, 8
	mov qword ptr [rdi], offset __add
	add rdi, 8
	mov qword ptr [rdi], offset __stop			

	#ALU
	mov rcx, rdi
	add rdi, 0x40

	#-mov qword ptr [rdi], offset __mov 					#mov opcode, 0x8
	add rdi, 8
	#-mov qword ptr [rdi], offset __movw                   #movw opcode, 0x9
	add rdi, 8
	#-mov qword ptr [rdi], offset __movws                  #movws opcode, 0xA
	add rdi, 8
	#-mov qword ptr [rdi], offset __movh                   #movh opcode, 0xB
	add rdi, 8
	#-mov qword ptr [rdi], offset __movhs                  #movhs opcode, 0xC
	add rdi, 8
	#-mov qword ptr [rdi], offset __movb                   #movb opcode, 0xD
	add rdi, 8
	#-mov qword ptr [rdi], offset __movbs                  #movbs opcode, 0xE
	add rdi, 8
	#-mov qword ptr [rdi], offset __movn                   #movn opcode, 0xF
	add rdi, 8
	#->mov qword ptr [rdi], offset __movne               #movne opcode, 0x
	add rdi, 8
	#->mov qword ptr [rdi], offset __movgt
	add rdi, 8
	#->mov qword ptr [rdi], offset __movge
	add rdi, 8
	#->mov qword ptr [rdi], offset __moveq
	add rdi, 8
	#->mov qword ptr [rdi], offset __movz
	add rdi, 8
	#->mov qword ptr [rdi], offset __movlt
	add rdi, 8
	#->mov qword ptr [rdi], offset __movle
	add rdi, 8
	#->mov qword ptr [rdi], offset __add
	add rdi, 8
	#->mov qword ptr [rdi], offset __sub
	add rdi, 8
	#->mov qword ptr [rdi], offset __inc
	add rdi, 8
	#->mov qword ptr [rdi], offset __dec
	add rdi, 8
	#->mov qword ptr [rdi], offset __mul
	add rdi, 8
	#->mov qword ptr [rdi], offset __smul
	add rdi, 8
	#->mov qword ptr [rdi], offset __div
	add rdi, 8
	#->mov qword ptr [rdi], offset __sdiv
	add rdi, 8
	#->mov qword ptr [rdi], offset __neg
	add rdi, 8
	#->mov qword ptr [rdi], offset __cmp
	add rdi, 8
	#->mov qword ptr [rdi], offset __and
	add rdi, 8
	#->mov qword ptr [rdi], offset __or
	add rdi, 8
	#->mov qword ptr [rdi], offset __not
	add rdi, 8
	#->mov qword ptr [rdi], offset __nand
	add rdi, 8
	#->mov qword ptr [rdi], offset __xor
	add rdi, 8
	#->mov qword ptr [rdi], offset __test
	add rdi, 8
	#->mov qword ptr [rdi], offset __rotl
	add rdi, 8
	#->mov qword ptr [rdi], offset __rotr
	add rdi, 8
	#->mov qword ptr [rdi], offset __shfl
	add rdi, 8
	#->mov qword ptr [rdi], offset __shfr
	add rdi, 8
	#->mov qword ptr [rdi], offset __nop
	add rdi, 8
	#->mov qword ptr [rdi], offset __seo
	add rdi, 8
	#->mov qword ptr [rdi], offset __lea
	add rdi, 136

	#Control Unit
	#->mov qword ptr [rdi], offset __go
	add rdi, 8
	#->mov qword ptr [rdi], offset __gone
	add rdi, 8
	#->mov qword ptr [rdi], offset __gogt
	add rdi, 8
	#->mov qword ptr [rdi], offset __goge
	add rdi, 8
	#->mov qword ptr [rdi], offset __goe
	add rdi, 8
	#->mov qword ptr [rdi], offset __gol
	add rdi, 8
	#->mov qword ptr [rdi], offset __gole
	add rdi, 8


	jmp rax									#Jump back to the calling function using the return address in RAX.



_vpu_start:									#Start the virtual processing unit.
	
	#Check to make sure a valid vpu vector has been passed.
	cmp rdi, 0x0
	je i_vpu_invalid_start

	#Move the VPU vector pointer to the correct register.
	mov r14, rdi

	#Pop the C return address off the stack and save it.
	pop rax
	mov qword ptr [r14 + 2072], rax			#Save the return address in the VPU vector.

	#Save the calling function's last stack address to the VPU vector.
	mov qword ptr [r14 + 2056], rsp

	#Move the main memory pointer into the r13 register for fast access.
	mov r13, qword ptr [r14 + 2040]

	#Set the VPU instruction pointer.
	mov rdi, 0x0

	#Finish prep
	mov r12, qword ptr [r14 + 2048]
	mov rsi, 0x0


	#Begin the fetch, decode, execute cycle.
	jmp ivpu_fetch


#A VPU start was requested without a valid VPU vector.
i_vpu_invalid_start:						
	pop rax
	jmp rax








