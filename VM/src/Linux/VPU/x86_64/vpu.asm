#The Ditto Virtual Machine
#=========================
#Virtual Processing Unit 
#=========================

.intel_syntax noprefix

.data

vpu_name:  .ascii "DittoIsGreat"
vpu_model: .ascii "Turing"
vpu_rev:   .ascii "1.0"

#TEST
p1msg: .ascii "Called prot mode!\n"
p2msg: .ascii "Called priv mode!\n"
p3msg: .ascii "Called IPRe comp!\n"
p4msg: .ascii "Memory lmt reach!\n"
p5msg: .ascii "Enter prot mode! \n"
p6msg: .ascii "Memory size fault\n"
p7msg: .ascii "Hardware Interr. \n"
p8msg: .ascii "Continue Exec..  \n"
p9msg: .ascii "Immediate jump.. \n"

.text
	.include "Control/enable.asm"
	#.include "ivpu.asm"
	.include "organized/fetch.asm"
	.include "organized/decoder.asm"
	.include "organized/read.asm"
	.include "organized/mmu_read.asm"
	.include "organized/execute.asm"
	.include "organized/immjmp.asm"
	.include "organized/faults.asm"
	.include "organized/dtu.asm"
	.include "organized/write.asm"
	.include "organized/mmu_write.asm"
	.include "organized/alu.asm"

