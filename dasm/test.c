/*
Test
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.c"
#include "dictionary.h"
#include "input.h"

int main(int argc, char* argv[]){

	printf("Start test...\n");

	dictionary* opcodes = _dictionary_create(3);

	int dat1 = 23;
	int dat2 = 24;

	void* test = &dat1;
	void* test2 = &dat2;

	_dictionary_insert(opcodes, test, _dictionary_hash("opcodeOne"));
	_dictionary_insert(opcodes, test2, _dictionary_hash("opcodeTwo"));
	_dictionary_insert(opcodes, test2, _dictionary_hash("opcodeThree"));

	int d1 = *((int*)_dictionary_lookup(opcodes, _dictionary_hash("opcodeTwo")));

	_dictionary_insert(opcodes, test, _dictionary_hash("opcodeFour"));

	int d2 = *((int*)_dictionary_lookup(opcodes, _dictionary_hash("opcodeTwo")));

	printf("Value: %d\n\n", d1);
	printf("Value: %d\n\n", d2);

	_dictionary_remove(opcodes, _dictionary_hash("opcodeTwo"));

	if(!_dictionary_lookup(opcodes, _dictionary_hash("opcodeTwo"))){

		printf("Deleted!\n\n");

	}

	_dictionary_destroy(opcodes);

	printf("End test...\n");
	
	return 0;

}