/*

Copyright 2016 Bobby Crawford (ozdevguy) | ozdevguy@gmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

========================================================================

The Ditto Virtual Machine | Ditto Assembler (dasm)

=========================================================================
Revision History

Written: March 2016 -> Bobby Crawford (ozdevguy)
Last Revision: N/A

=========================================================================

symtable.c

This file contains the functions necessary to maintain a symbol table. The symbol table
is used to define and organize various parts of the assembly program.


*/

//Create a new symbol table.
dictionary* _symtable_create(){

	//Create a symbol table with a starting size of 10.
	dictionary* st = _dictionary_create(10);


}

//Destroy a symbol table.
void _symtable_destroy(dictionary* symtable){

	printf("\n\nDestroy a symtable...\n\n");
	dictionary_entry* entry;
	symbol* data;
	stub *st, *tmp;

	//Loop through the dictionary to get all values without relying on hash indices.
	while((entry = _dictionary_loop_get_entry(symtable)) != 0){

		data = entry->data;

		if(data){

			free(data->label);
			st = data->stubs;

			while(st){

				tmp = st;
				st = tmp->next;
				free(tmp);

			}

			free(data);

		}

	}

	_dictionary_destroy(symtable);

}

//Creare a symbol.
symbol* _symtable_set_symbol(dictionary* table, char* label){

	symbol* sym;

	if(!label || !table)
		return 0;

	//Create a symbol hash.
	int hash = _dictionary_hash(label);

	//Check to make sure the symbol doesn't already exist.
	if((sym = _dictionary_lookup(table, hash)) != 0)
		return sym;

	//If the symbol has not been created, do so now.
	int llength = strlen(label);
	char* lb = (char*)calloc(llength, 1);

	strcpy(lb, label);

	symbol* ns = (symbol*)malloc(sizeof(symbol));

	ns->hash = hash;
	ns->label = lb;
	ns->lsize = llength;
	ns->def = 0;
	ns->stubs = 0;

	_dictionary_insert(table, ns, hash);

	return ns;

}

//Get a symbol.
symbol* _symtable_get_symbol(dictionary* table, char* label){

	if(!table || !label)
		return 0;

	return _dictionary_lookup(table, _dictionary_hash(label));

}

//Check if a symbol is defined.
bool _symtable_symbol_defined(symbol* sym){

	if(!sym)
		return 0;

	if(sym->def)
		return true;

	return false;

}

//Get a symbol's reference type and value.
bool _symtable_symbol_getdef(symbol* sym, short* type, unsigned long* ref){

	if(!sym)
		return false;

	if(!(sym->def))
		return false;

	*type = sym->r_type;
	*ref = sym->ref;
	return true;

}

//Define a symbol.
void _symtable_symbol_define(symbol* sym, short type, unsigned long ref){

	if(!sym)
		return;

	sym->def = true;
	sym->r_type = type;
	sym->ref = ref;

	return;

}

//Get the linked list of stubs from a symbol.
stub* _symtable_symbol_stub_get(symbol* sym){

	return sym->stubs;
}

stub* _symtable_symbol_stub_getl(dictionary* table, char* label){

	symbol* sym;

	if((sym = _symtable_get_symbol(table, label)))
		return sym->stubs;

	return 0;
}

//Add a stub to a symbol.
stub* _symtable_symbol_stub_add(symbol* sym, unsigned long ref){

	stub* ns = (stub*)malloc(sizeof(stub));
	ns->ref = ref;
	ns->next = 0;

	stub* cs = sym->stubs;


	if(cs){

		while(cs->next)
			cs = cs->next;
		cs->next = ns;

	}
	else{

		sym->stubs = ns;

	}

	return ns;

}


