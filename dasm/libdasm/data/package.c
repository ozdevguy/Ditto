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

package.c

This file conttains the packaging functions, which take the major data tables and packages/unpackages them
into/from object file formats. All dynamically allocated data is placed in a data pool, and the pointers in each of 
the major data table structures are changed to reference its data's offset within the data pool.


*/

typedef struct{

	//Symbol pool.
	byte*  spool;

	//Size of symbol pool.
	uint32_t spool_size;

	//Number of symbols.
	uint32_t spool_total;

	//Data pool.
	byte* dpool;

	//Size of data pool.
	uint32_t dpool_size;

	//Number of items in data pool.
	uint32_t dpool_total;

} packager;


//Package the symbol table.
static void data_package_symtable(dictionary* symtable, packager* np){

	bool arch32 = true;
	int st_total;
	unsigned long current_size;
	byte* current_object;
	dictionary_entry* entry;
	symbol* sym;
	stub* st;

	//Symbol storage specification: | label length (1 byte) | flags (1 byte) | ref (4 or 8 bytes) | end (4 or 8 bytes) | label (variable, indicated in label length) | stubs |

	uint8_t llength, flags;
	uint32_t end;
	uint32_t ref32;
	uint64_t ref64;



	//Get each symbol table entry.
	while((entry = _dictionary_loop_get_entry(symtable)) != 0){

		sym = (symbol*)entry->data;

		//Set the symbol length.
		llength = sym->lsize;

		//Now, set the flags.
		flags = sym->r_type;

		if(sym->def)
			flags += 128;

		//Count the number of stubs.
		st_total = 0;
		st = sym->stubs;

		while(st){
				
			st_total++;
			st = st->next;

		}

		if(arch32){

			//Set the symbol reference.
			ref32 = sym->ref;




		}
		else{

			//Set the symbol reference.
			ref64 = sym->ref;
			flags += 64;


		}



	}





}


//Packager
packaged_object_data* _data_package(dictionary* symtable, data_table* dattable){

	packaged_object_data* package;
	packager* np;

	np = (packager*)malloc(sizeof(packager));
	np->dpool_size = 0;
	np->spool_size = 0;
	np->dpool_total = 0;
	np->spool_total = 0;
	np->dpool = 0;
	np->spool = 0;

	data_package_symtable(symtable, np);

	return package;

}