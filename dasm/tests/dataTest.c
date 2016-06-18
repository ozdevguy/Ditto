typedef unsigned char byte;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../libdasm/dictionary.h"
#include "../libdasm/data.h"


void main(int argc, char* argv[]){

	
	dictionary* symtable = _symtable_create();
	data_table* dtable = _dattable_create();

	//Create some symbols.
	symbol* sym1 = _symtable_set_symbol(symtable, "_start");
	symbol* sym2 = _symtable_set_symbol(symtable, "msg1");
	symbol* sym3 = _symtable_set_symbol(symtable, "msg2");

	//Create some data entries, and define the symbols as such.
	int* id1;
	char* msg1 = "Hello world!\n";
	int msg1len = strlen(msg1);
	char* msg1a = (char*)malloc(msg1len);
	memcpy(msg1a, msg1, msg1len);

	_dattable_add(dtable, DATA_ASCII, msg1len, (byte*)msg1a, id1);
	_symtable_symbol_define(sym2, SYMBOL_REF_DATA, *id1);

	printf("%s\n", _symtable_get_symbol(symtable, "_start")->label);

	_symtable_destroy(symtable);
	

	



	return;
}