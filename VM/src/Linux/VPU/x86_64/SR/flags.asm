#The Ditto Virtual Machine VPU
#=============================
#Flag register control 
#x86_64 VPU FLAGS register = RSI write 0 = RAX, write 1 = RDX
#User write 0 for control transfer. Use write 1 for data.

#ZF (FLAGS bit 0 -> 1)

i_vpu_flags_zf_g:					#Get zero flag.
	mov rdx, rsi
	and rdx, 0x1
	jmp rax

i_vpu_flags_zf_1:					#Set zero flag to true.
	or rsi, 0x1
	jmp rax

i_vpu_flags_zf_0:					#Set zero flag to false.
	mov rdx, 0xFFFFFFFE
	and rsi, rdx
	jmp rax





#OF (FLAGS bit 1 -> 2)

i_vpu_flags_of_g:					#Get overflow flag.
	mov rdx, rsi
	and rdx, 0x2
	shr rdx, 0x1
	jmp rax

i_vpu_flags_of_1:					#Set overflow flag to true.
	or rsi, 0x2
	jmp rax

i_vpu_flags_of_0:					#Set overflow flag to false.
	mov rdx, 0xFFFFFFFD
	and rsi, rdx
	jmp rax




#SD (FLAGS bit 2 -> 4)

i_vpu_flags_sd_g:					#Get stack direction flag.
	mov rdx, rsi
	and rdx, 0x4
	shr rdx, 0x2
	jmp rax

i_vpu_flags_sd_1:					#Set stack direction flag to true.
	or rsi, 0x4
	jmp rax

i_vpu_flags_sd_0:					#Set stack direction flag to false.
	mov rdx, 0xFFFFFFFB
	and rsi, rdx
	jmp rax



#GT (FLAGS bit 3 -> 8)

i_vpu_flags_gt_g:					#Get greater than flag.
	mov rdx, rsi
	and rdx, 0x8
	shr rdx, 0x3
	jmp rax

i_vpu_flags_gt_1:					#Set greater than flag to true.
	or rsi, 0x8
	jmp rax

i_vpu_flags_gt_0:					#Set greater than flag to false.
	mov rdx, 0xFFFFFFF7
	and rsi, rdx
	jmp rax



#LT (FLAGS bit 4 -> 16)

i_vpu_flags_lt_g:					#Get less than flag.
	mov rdx, rsi
	and rdx, 0x10
	shr rdx, 0x4
	jmp rax

i_vpu_flags_lt_1:					#Set less than flag to true.
	or rsi, 0x10
	jmp rax

i_vpu_flags_lt_0:					#Set less than flag to false.
	mov rdx, 0xFFFFFFEF
	and rsi, rdx
	jmp rax



#NE (FLAGS bit 5 -> 32)

i_vpu_flags_ne_g:					#Get negative flag.
	mov rdx, rsi
	and rdx, 0x20
	shr rdx, 0x5
	jmp rax

i_vpu_flags_ne_1:					#Set negative flag to true.
	or rsi, 0x20
	jmp rax

i_vpu_flags_ne_0:					#Set negative flag to false.
	mov rdx, 0xFFFFFFDF
	and rsi, rdx
	jmp rax




#CA (FLAGS bit 6 -> 64)

i_vpu_flags_ca_g:					#Get carry flag.
	mov rdx, rsi
	and rdx, 0x40
	shr rdx, 0x6
	jmp rax

i_vpu_flags_ca_1:					#Set carry flag to true.
	or rsi, 0x40
	jmp rax

i_vpu_flags_ca_0:					#Set carry flag to false.
	mov rdx, 0xFFFFFFBF				
	and rsi, rdx
	jmp rax


#FLAGS bits 7 & 8 are currently not in use.


#-->Privileged mode ONLY flags...


#SI (FLAGS bit 9 -> 512)

i_vpu_flags_si_g:					#Get the software interrupt enable flag.
	mov rdx, rsi
	and rdx, 0x200
	shr rdx, 0x9
	jmp rax

i_vpu_flags_si_1:					#Set software interrupt enable to true.
	or rsi, 0x200
	jmp rax

i_vpu_flags_si_0:					#Set software interrupt enable to false.
	mov rdx, 0xFFFFFDFF
	and rsi, rdx
	jmp rax


#HI (FLAGS bit 10 -> 1024)

i_vpu_flags_hi_g:					#Get the hardware interrupt enable flag.
	mov rdx, rsi
	and rdx, 0x400
	shr rdx, 0xA
	jmp rax

i_vpu_flags_hi_1:					#Set hardware interrupt enable to true.
	or rsi, 0x400
	jmp rax

i_vpu_flags_hi_0:					#Set hardware interrupt enable to false.
	mov rdx, 0xFFFFFBFF
	and rsi, rdx
	jmp rax


#PE (FLAGS bit 11 -> 2048)

i_vpu_flags_pe_g:					#Get the paging enabled flag.
	mov rdx, rsi
	and rdx, 0x800
	shr rdx, 0xB
	jmp rax

i_vpu_flags_pe_1:
	or rsi, 0x800
	jmp rax

i_vpu_flags_pe_0:
	mov rdx, 0xFFFFF7FF
	and rsi, rdx
	jmp rax



#SE (FLAGS bit 12 -> 4096)

i_vpu_flags_se_g:					#Get the segmentation enabled flag.
	mov rdx, rsi
	and rdx, 0x1000
	shr rdx, 0xC
	jmp rax

i_vpu_flags_se_1:
	or rsi, 0x1000
	jmp rax

i_vpu_flags_se_0:
	mov rdx, 0xFFFFEFFF
	and rsi, rdx
	jmp rax




#PR (FLAGS bit 13 -> 8192)

i_vpu_flags_pr_g:					#Get the protected mode enabled flag.
	mov rdx, rsi
	and rdx, 0x2000
	shr rdx, 0xD
	jmp rax

i_vpu_flags_pr_1:
	or rsi, 0x2000
	jmp rax

i_vpu_flags_pr_0:
	mov rdx, 0xFFFFDFFF
	and rsi, rdx
	jmp rax


	

	


