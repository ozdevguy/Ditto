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
	symbol* sym4 = _symtable_set_symbol(symtable, "_newFunc");
	symbol* sym5 = _symtable_set_symbol(symtable, "_func2");
	symbol* sym6 = _symtable_set_symbol(symtable, "dk_it");
	symbol* sym7 = _symtable_set_symbol(symtable, "wakawaka");
	symbol* sym8 = _symtable_set_symbol(symtable, "flack");
	symbol* sym9 = _symtable_set_symbol(symtable, "duck");
	symbol* sym10 = _symtable_set_symbol(symtable, "wassawaka");
	symbol* sym11 = _symtable_set_symbol(symtable, "arm");
	


	//printf("%d\n", symtable->total);
	//printf("%d\n", symtable->size);

	
	//Define each symbol...
	_symtable_symbol_define(sym1, SYMBOL_REF_TEXT, 1234567);
	_symtable_symbol_define(sym2, SYMBOL_REF_TEXT, 23455666);
	_symtable_symbol_define(sym3, SYMBOL_REF_TEXT, 48733384);
	_symtable_symbol_define(sym4, SYMBOL_REF_BSS, 3838);

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

	_symtable_symbol_stub_add(sym4, 222);
	

	//Package the symbol table.
	packaged_object_data dat = _data_package(symtable, dtable);


	unpacked_object_data retDat = _data_unpack(&dat);

	_data_free_packaged(dat);


	symbol* sym15 = _symtable_get_symbol(retDat.sym_table, "_func_new");

	printf("%s: %ld\n", sym15->label, sym15->ref);
	printf("Symbol table size: %ld\n", dat.symbol_table_size);

	_symtable_destroy(symtable);
	_dattable_destroy(dtable);
	_symtable_destroy(retDat.sym_table);
	

	return;
}