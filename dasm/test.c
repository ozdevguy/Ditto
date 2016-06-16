/*
Test
*/

#include "libdasm.h"

int main(int argc, char* argv[]){

	printf("Start test...\n");

	_parser_begin("test.txt");

	/*

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


	input_descriptor* id = _input_create_descriptor();

	_input_add_open(id, "test.txt");

	fline* ln = _input_get_line(id);
	

	while(ln != 0){

		ln = _input_get_line(id);

		if(!ln)
			break;

		printf("%s\n", ln->line);

	}

	_input_cleanup(id);
	*/



	printf("End test...\n");
	
	return 0;

}