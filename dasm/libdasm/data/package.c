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


static void data_package_symobject(packaged_object_data* p, byte* object, unsigned int size){

	if(!p || !object || !size)
		return;

	if(!p->symbol_table){

		p->symbol_table = (byte*)malloc(size);
		p->symbol_table_size = size;

		memcpy((void*)p->symbol_table, (void*)object, size);

		return;

	}
	else{

		//Create a larger pool.
		byte* tmp = p->symbol_table;
		p->symbol_table = (byte*)malloc(p->symbol_table_size + size);

		//Copy the contents of the old pool to the new pool.
		memcpy((void*)p->symbol_table, (void*)tmp, p->symbol_table_size);

		//Copy the new object to the end of the new pool.
		memcpy((void*)(p->symbol_table + p->symbol_table_size), (void*)object, size);

		p->symbol_table_size += size;

		free(tmp);

		return;

	}

}


//Unpack the symbol table.
static void data_unpack_symtable(packaged_object_data* p, unpacked_object_data* u){

	//Create a new symbol table.
	dictionary* symtable = _symtable_create();
	byte* pool = p->symbol_table;

	unsigned long i = 0;

	/*
	uint32_t symbol_size = *((uint32_t*)(p->symbol_table + i));

	i += 35;

	uint32_t symbol_size2 = *((uint32_t*)(p->symbol_table + i));

	i += 19;

	uint32_t symbol_size3 = *((uint32_t*)(p->symbol_table + i));

	printf("%d\n", symbol_size);
	printf("%d\n", symbol_size2);
	printf("%d\n", symbol_size3);
	*/

	while(i < p->symbol_table_size){

		uint32_t symbol_size = *((uint32_t*)(p->symbol_table + i));

		i += 4;
		uint8_t llength = *((uint8_t*)(p->symbol_table + i));

		i++;
		uint8_t flags = *((uint8_t*)(p->symbol_table + i));

		i++;
		uint32_t ref = *((uint8_t*)(p->symbol_table + i));

		i += 4;

		//Get the label.
		char label[llength + 1];

		memcpy(label, (p->symbol_table + i), llength);

		label[llength] = 0;

		printf("Label length: %d\n", llength);

		i += llength;

		//Create the symbol table entry.
		symbol* sym = _symtable_set_symbol(symtable, label);


		if(ref)
			_symtable_symbol_define(sym, SYMBOL_REF_TEXT, ref);

		int j = (symbol_size - 10 - llength) / 4;

		for(j; j > 0; j--){

			i += 4;

		}

		printf("%s\n", label);

		printf("%ld\n", i);

	}

}


//Package the symbol table.
static void data_package_symtable(dictionary* symtable, packaged_object_data* p){

	bool arch32 = true;

	dictionary_entry* entry;
	byte* current_object;
	symbol* sym;
	stub* st;

	unsigned int current_size;
	unsigned int st_total;
	uint8_t llength;
	uint8_t flags;


	//Get each symbol table entry.
	while((entry = _dictionary_loop_get_entry(symtable)) != 0){

		sym = (symbol*)entry->data;

		if(sym){

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

				//Now, calculate the total size of this symbol object.
				current_size = 10 + llength + (st_total * 4);

				//Create the object on the heap.
				current_object = (byte*)malloc(current_size);

				//Copy over the symbol object size.
				uint32_t* symsize = (uint32_t*)(current_object);
				*symsize = current_size;

				//Copy over the label length.
				uint8_t* ll = (uint8_t*)(current_object + 4);
				*ll = llength;

				//Copy over the flags.
				uint8_t* fl = (uint8_t*)(current_object + 5);
				*fl = flags;

				//Copy over the reference.
				uint32_t* ref = (uint32_t*)(current_object + 6);
				*ref = sym->ref;

				//Copy over the label.
				memcpy((current_object + 10), sym->label, llength);

				//Now, copy each stub.
				st = sym->stubs;
				int i = (10 + llength);

				while(st){

					uint32_t* stub = (uint32_t*)(current_object + i);
					*stub = st->ref;

					st = st->next;
					i += 4;

				}

				//Complete this process by writing the new symbol object to the symbol table pool.
				data_package_symobject(p, current_object, current_size);
				free(current_object);
			}
			else{

				//64 BIT ARCHITECTURE TARGET
			


			}

		}


	}




}


//Packager
packaged_object_data _data_package(dictionary* symtable, data_table* dattable){

	packaged_object_data p;

	p.d_table = 0;
	p.d_table_size = 0;
	p.bss_table = 0;
	p.bss_table_size = 0;
	p.symbol_table = 0;
	p.symbol_table_size = 0;

	data_package_symtable(symtable, &p);

	return p;

}


//Unpacker.
unpacked_object_data _data_unpack(packaged_object_data* data){

	unpacked_object_data u;

	u.sym_table = 0;
	u.dat_table = 0;

	data_unpack_symtable(data, &u);

	return u;

}