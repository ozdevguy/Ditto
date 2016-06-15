/*

Copyright 2016 Bobby Crawford (ozdevguy)

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

dictionary.c

This file contains the functions used to build a fast lookup data dictionary utilizing a hash table
with linear probing.


*/

//Calculate a hash value (internal use only).
static unsigned int hash(char* input){

	unsigned int hashval = 0;
	int i = 0;

	while(input[i++])
		hashval += (input[i - 1] * i);

	return hashval;


}

//Re-insert an item into an expanded table.
static void dictionary_reinsert(dictionary* newTable, dictionary_entry* entry){

	//Get the theoretical position in the new hash table for this entry.
	int i = entry->hashval % newTable->size;

	//Check if the first mapped address is available.
	if(newTable->table[i].hashval){

		while(newTable->table[i].hashval)			
			i = (i % size) + 1;
		
		i--;

	}

	//Set the value.
	source->table[i].hashval = hashval;
	source->table[i].data = data;
	source->total++;


}

//Expand the dictionary if needed (internal use only).
static void expand_dictionary(dictionary* source){

	int i, total;

	dictionary* nt;

	if(!source)
		return;

	total = source->size;

	nt = _dictionary_create(source->size * 2);

	for(i = 0; i < total; i++){

		if(source->table[i].hashval)
			dictionary_reinsert(nt, source->table[i]);


	}

	//Perform the swap..
	source->total = nt->total;
	source->size = nt->size;

	free(source->table);
	source->table = nt->table;
	free(nt);


}

//Create a new hash table dictionary.
dictionary* _dictionary_create(unsigned int startSize){

	//Ensure the start size is valid.
	if(!startSize)
		return 0;

	//Create a new dictionary object.
	dictionary* nt = (dictionary*)malloc(sizeof(dictionary));

	//Set defaults for the dictionary object.
	nt->total = 0;
	nt->size = startSize;

	//Create the initial table.
	nt->table = (dictionary_entry*)malloc(sizeof(dictionary_entry) * startSize);
	memset(nt->table, 0, startSize);

	return nt;

}



//Destroy a hash table dictionary.
unsigned short _dictionary_destroy(dictionary* source){

	int i;

	if(!source)
		return 0;

	if(source->table){

		for(i = 0; i < source->size; i++){

			if(source->table[i]->llength)
				free(source->table[i].label);

		}

		free(source->table);
	}

	free(source);

	return 1;

}


//Insert an item into the hash table.
unsigned short _dictionary_insert(dictionary* source, void* object, char* label){

	unsigned int i, size, hashval;

	hashval = hash(label);

	if(!source)
		return 0;

	size = source->size;
	i = hashval % source->size;

	//No room... Expand the hash table.
	if(source->total == size)
		expand_dictionary(source);

	
	//Check if the first mapped address is available.
	if(source->table[i].hashval){

		while(source->table[i - 1].hashval)			
			i = (i % size) + 1;
		
		i--;

	}

	//Set the value.
	source->table[i].hashval = hashval;
	source->table[i].data = data;
	source->total++;

	return 1;


}

//Pull an item from the dictionary.
void* _lookup(dictionary* source, unsigned int hashval){

	int i, j, size;

	i = hashval % source->size;
	size = source->size;
	j = 0;

	//Not in the directly mapped index? It doesn't exist!
	if(!source->table[i].hashval)
		return 0;

	if(source->table[i].hashval != hashval){

		while(source->table[i - 1].hashval != hashval && j++ < size)
			i = (i % size) + 1;

		i--;

		if(j >= size)
			return 0;

	}

	return source->table[i].data;

}

//Remove an item from the dictionary.
unsigned short _remove(dictionary* source, unsigned int hashval){

	int i, total;

	dictionary* nt;

	if(!source)
		return;

	total = source->size;

	nt = _createDictionary(source->size);

	for(i = 0; i < total; i++){

		if(source->table[i].hashval && source->table[i].hashval != hashval)
			_insert(nt, source->table[i].hashval, source->table[i].data);

		else if(source->table[i].hashval == hashval && source->table[i].data)
			free(source->table[i].data);

	}

	//Perform the swap..
	source->total = nt->total;
	source->size = nt->size;

	free(source->table);
	source->table = nt->table;
	free(nt);


}