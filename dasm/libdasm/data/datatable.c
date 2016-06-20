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

datatable.c

This file contains the functions necessary to maintain a data table. The data table is where
items defined in the "data" section of an assembly program are stored for the object file.


*/

//Create a new data table.
data_table* _dattable_create(){

	data_table* dtable = (data_table*)malloc(sizeof(data_table));

	//Start with enough space for 10 data entrires.
	dtable->dasize = 5;
	dtable->total = 0;
	dtable->entries = (data_entry*)malloc(sizeof(data_entry) * 5);

	return dtable;

}

//Add to the data table.
data_entry* _dattable_add(data_table* table, short type, unsigned int size, byte* data, int* id){

	if(!table || !data)
		return 0;

	//Resize the table if necessary...
	if(table->total == table->dasize){

		unsigned int newSize = table->dasize * 2;

		data_entry* newTable = (data_entry*)malloc(sizeof(data_entry) * newSize);
		memcpy(newTable, table->entries, table->dasize);

		free(table->entries);

		table->dasize = newSize;

		table->entries = newTable;

	}

	table->entries[table->total].id = table->total;
	table->entries[table->total].type = type;
	table->entries[table->total].size = size;
	table->entries[table->total].data = data;
	*id = table->total;

	return &(table->entries[table->total++]);

}

//Set the alignment for a data table entry.
void _dattable_entry_align(data_entry* entry, short alignment){

	if(!entry)
		return;

	entry->alignment = alignment;

}

//Get a data entry from the data table.
data_entry* _dattable_get(data_table* table, unsigned int id){

	if(!table)
		return 0;

	return &(table->entries[id]);

}

void _dattable_destroy(data_table* table){

	int i;

	if(!table)
		return;

	for(i = 0; i < table->dasize; i++){

		if(table->entries[i].data)
			free(table->entries[i].data);

	}

	free(table->entries);
	free(table);

}






