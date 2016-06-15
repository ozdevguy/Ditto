/*

DASM


*/


#include "libdasm.h"


int main(int argc, char* argv[]){


	void* ptr1;
	void* ptr2;
	void* ptr3;
	void* ptr4;

	ptr1 = dasm_malloc(23);
	ptr2 = dasm_malloc(24);
	ptr3 = dasm_malloc(25);
	ptr4 = dasm_malloc(26);

	dasm_mfree();

	return 1;

}