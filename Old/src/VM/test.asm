.intel_syntax noprefix

//Data...
.data

EatMsg: .ascii  "Eat at Joe's\n"

.text

.global _start

t2:
	mov eax, 4
	mov ebx, 1
	mov ecx, offset EatMsg
	mov edx, 13
	int 0x80
	mov eax, 1
	mov ebx, 0
	int 0x80
	
_start: 
	nop
	mov eax, 4
	mov ebx, 1
	mov ecx, offset EatMsg
	mov edx, 13
	int 0x80
	jmp t2
