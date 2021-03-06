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

dstructs.c

This file contains the structures used to build the data, symbol, and bss tables.


*/



/* DATA TABLE */

enum{DATA_DWORD, DATA_WORD, DATA_ASCII};

//A data table entry.
typedef struct{

	//Data id.
	int id;

	//Data type.
	short type;

	//Data alignment.
	short alignment;

	//Data size.
	unsigned int size;

	//Data
	byte* data;

} data_entry;


//Data table.
typedef struct{

	//Total items.
	int total;

	//Data entry array size.
	int dasize;

	//Array of data entries.
	data_entry* entries;

} data_table;


/* SYMBOL TABLE */
enum{SYMBOL_UNDEF, SYMBOL_REF_DATA, SYMBOL_REF_BSS, SYMBOL_REF_TEXT};

//A text segment stub.
struct stub{

	//Stub address.
	unsigned long ref;

	//Next stub.
	struct stub* next;

};

typedef struct stub stub;

typedef struct{

	//Symbol hash.
	unsigned int hash;

	//Label.
	char* label;

	//Label size.
	int lsize;

	//Defined?
	bool def;

	//Symbol reference type.
	uint8_t r_type;

	//Symbol reference.
	unsigned long ref;

	//Symbol stubs.
	stub* stubs;

} symbol;


/* PACKAGED OBJECT DATA */

typedef struct{

	//Data table.
	byte* d_table;
	unsigned long d_table_size;

	//BSS table.
	byte* bss_table;
	unsigned long bss_table_size;

	//Symbol table.
	byte* symbol_table;
	unsigned long symbol_table_size;


} packaged_object_data;


/* UNPACKAGED OBJECT DATA */

typedef struct{

	//Symbol table.
	dictionary* sym_table;

	//Data table.
	data_table* dat_table;

} unpacked_object_data;



typedef struct{


	//Format type.
	uint8_t frmt_type;

	//Data table starting position.
	uint32_t symtable_start;

	//Symbol table size.
	uint32_t symtable_size;





} file_info;