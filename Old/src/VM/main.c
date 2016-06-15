/*
The Ditto Virtual Machine
Written by: Bobby Crawford
Email: ozdevguy@gmail.com
File: main.c
Description: This file contains functions responsible for starting an instance of the Ditto virtual machine (DVM)
*/


#include <stdlib.h>
#include <stdio.h>

//Include the proper libraries.
#ifdef __linux__
	
	extern char edata, etext, end;

#endif

typedef unsigned char byte;


//Set the VPU vector.
int _dt_set_vpu_vector32(){

	byte* vpu_vector;

	if(!(vpu_vector = (byte*)malloc(1078)))
		return 0;

	return 1;
	

}

int _dt_set_vpu_vector64(){

	return 1;
	
}

int main(int argc, char* argv[]){


}