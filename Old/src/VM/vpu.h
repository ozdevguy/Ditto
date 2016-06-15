/*
The Ditto Virtual Machine
Written by: Bobby Crawford
Email: ozdevguy@gmail.com
File: main.c
Description: This file contains prototypes that correspond to setting up the VPU, which is written in platform dependent assembly.
When compiling the virtual machine, you must include the correct VPU object file for your build.
*/

//Setup the VPU.
void _dt_vpu_init(byte* vpu_vector, byte* reg_vector);

//Connect memory to the virtual memory bus.
void _dt_vpu_membus_conn(byte* memStart, unsigned long memsize);

/*
//Connect virtual device to I/O interrupt line 1.
int _dt_vpu_ioln1_conn();

//Connect virtual device to I/O line 2.
int _dt_vpu_ioln2_conn();

//Connect virtual device to I/O line 3.
int _dt_vpu_ioln3_conn();

//Connect virtual device to I/O line 4.
int _dt_vpu_ioln4_conn();

//Connect virtual device to I/O line 5.
int _dt_vpu_ioln5_conn();

//Connect virtual device to I/O line 6.
int _dt_vpu_ioln6_conn();

//Connect virtual device to I/O line 7.
int _dt_vpu_ioln7_conn();

//Connect virtual device to I/O line 8.
int _dt_vpu_ioln8_conn();

//Connect virtual device to I/O line 9.
int _dt_vpu_ioln9_conn();

//Connect virtual device to I/O line 10.
int _dt_vpu_ioln10_conn();

*/

//Start; hand control to the VPU.
int _dt_vpu_start();



