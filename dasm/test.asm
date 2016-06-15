#DASM TEST PROGRAM -> WRITTEN BY BOBBY CRAWFORD 

.arch 32

[section data]

msg1: ascii "Hello world!\n"
msg2: ascii "How are you?\n"
int1: word 12876
int2: signed_word -2
int3: word 1212
float1: float32 3.1415

[section text]

__start:
	ld r1, [int1]
	ld r2, [int2]
	add r3, r1, r2
	str [0x40], r3
	stop

