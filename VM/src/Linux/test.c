#include "libditto_linux.h"
#include <time.h>
#include <sys/mman.h>

extern char etext;

void main(int argc, char* argv[]){

	clock_t begin, end;
	double time_spent;

	int i = 1;

	vpu_vector* vect;
	void* memory;
	int* dat;

	vect = _sys_create_vpu_vector();

	memory = _sys_auto_memory_setup(vect, 64000);
	dat = (int*)memory;

	/*
	printf("Text segment size: %d\n", *((int*)&etext));
	mlock(0, *((long*)&etext));
	mlock(vect, 3000);
	*/

	/*
	//TEST 1: IMMEDIATE MEMORY ADDRESSING (ld r2, [128])
	dat[0] = 593920;		//ld instruction.
	dat[1] = 128;			//Memory address.
	dat[32] = 8675309;		//Place data at memory address.
	*/

	
	//TEST 2: REGISTER MEMORY ADDRESSING (ld r2, r3)
	/*
	vect[262] = 128;   //Place 128 in register r3.
	dat[0] = 2691584;		//ld instruction.
	dat[1] = 2147483648;    //Second word, with Ru set.
	dat[32] = 8675310;      //Place data at memory address.
	
	/*
	*/

	//TEST 3: OFFSET MEMORY ADDRESSING (ld r2, [r1 + 64])
	/*
	vect[260] = 64; //Place 64 in register r1
	dat[0] = 2691072;     //ld instruction.
	dat[1] = 64;  //Second word, without Ru set.
	dat[32] = 8675309;

	//TEST 4: OFFSET MEMORY ADDRESSING (ld r2, [r1 - 128])

	vect[260] = 192;
	dat[0] = 2691072;     //ld instruction.
	dat[1] = 1073741888;  //Second word, without Ru set.
	dat[32] = 8675309;
	*/

	/*
	TEST 5: FIRST BIG TEST
	ld r1, [128]
	ld r2, [132]
	add r3, r1, 40000000
	str [256], r3
	str [260], r3
	str [264], r3
	str [268], r3
	str [272], r3
	str [276], r3
	stop


	TEST 6: STACK TEST
	
	*/





	vect[260] = 624;
	vect[261] = 80086;
	vect[262] = 180;

	//vect[262] = 5;

	/*
	dat[0] = 83886336;
	dat[1] = 40000000;

	dat[2] = 100925440;
	*/

	dat[0] = 19595777;
	dat[1] = 1073741888;
	dat[2] = 100925440;


	_vpu_initialize(vect);


	begin = clock();
	_vpu_start(vect);
	end = clock();

	//long* data = (long*)vect;

	//time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	//printf("Executed one hundred sixty two million jump instructions in %lf seconds\n", time_spent);

	/*
	for(i = 0; i < 262; i++){
		
		void* dat = (void*)vect[i];

		printf("Data: %p\n", dat);

	}
	*/


	for(i = 260; i < 276; i++){

		printf("Value: %ld | Time: %lf\n", vect[i], (double)(end - begin) / CLOCKS_PER_SEC);
	}

	for(i = 30; i < 35; i++){

		printf("Value in memory: %d\n", dat[i]);

	}



	_sys_memory_disconnect(vect);
	_sys_destroy_vector(vect);


}