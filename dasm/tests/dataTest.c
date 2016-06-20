typedef unsigned char byte;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "../libdasm/dictionary.h"
#include "../libdasm/data.h"


void main(int argc, char* argv[]){


	dictionary* symtable = _symtable_create();
	data_table* dtable = _dattable_create();

	
	//Create some symbols.
	symbol* sym1 = _symtable_set_symbol(symtable, "_start");
	symbol* sym2 = _symtable_set_symbol(symtable, "_func_new");
	symbol* sym3 = _symtable_set_symbol(symtable, "_func");

	//Define each symbol...
	_symtable_symbol_define(sym1, SYMBOL_REF_TEXT, 1234567);
	_symtable_symbol_define(sym2, SYMBOL_REF_TEXT, 23455666);
	_symtable_symbol_define(sym3, SYMBOL_REF_TEXT, 48733384);

	//Add stubs to sym1.
	_symtable_symbol_stub_add(sym1, 12);
	_symtable_symbol_stub_add(sym1, 34);

	//Add stubs to sym2.
	_symtable_symbol_stub_add(sym2, 56);
	_symtable_symbol_stub_add(sym2, 78);
	_symtable_symbol_stub_add(sym2, 910);
	_symtable_symbol_stub_add(sym2, 1112);

	//Add stub to sym3.
	_symtable_symbol_stub_add(sym3, 1314);

	//Package the symbol table.
	packaged_object_data dat = _data_package(symtable, dtable);

	_data_unpack(&dat);



	_symtable_destroy(symtable);
	
	



	return;
}