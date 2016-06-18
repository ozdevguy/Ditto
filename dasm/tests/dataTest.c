typedef unsigned char byte;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../libdasm/dictionary.h"
#include "../libdasm/data.h"


void main(int argc, char* argv[]){

	dictionary* symtable = _symtable_create();

	symbol* sym1 = _symtable_set_symbol(symtable, "_start");
	symbol* sym2 = _symtable_set_symbol(symtable, "msg1");
	symbol* sym3 = _symtable_set_symbol(symtable, "msg2");

	_symtable_symbol_define(sym1, SYMBOL_REF_TEXT, 23);
	_symtable_symbol_define(sym2, SYMBOL_REF_TEXT, 24);
	_symtable_symbol_define(sym3, SYMBOL_REF_TEXT, 25);

	_symtable_symbol_stub_add(sym1, 256);
	_symtable_symbol_stub_add(sym1, 512);
	_symtable_symbol_stub_add(sym1, 1024);

	printf("%s\n", _symtable_get_symbol(symtable, "_start")->label);

	return;
}