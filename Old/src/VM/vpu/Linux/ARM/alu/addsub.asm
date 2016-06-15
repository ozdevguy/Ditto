//The Ditto Virtual Machine | Version 1.0
//Written by Bobby Crawford

//ALU-ADD - This file represents the various manifestations of the add operation.

_dt_alu_add:
	add r3, r1, r2 //r3 = write 1, r1 = read 1, r2 = read 2
	b _dt_control_ret

_dt_alu_sub:
	sub r3, r1, r2 //r3 = write 1, r1 = read 1, r2 = read 2
	b _dt_control_ret

_dt_alu_inc: 
	add r3, r1, $1 //r3 = write 1, r1 = read 1
	b _dt_control_ret

_dt_alu_dec: 
	sub r3, r1, $1 //r3 = write 1, r1 = read 1
	b _dt_control_ret
