/*
The Ditto Virtual Machine | Ditto Assembler (DASM) 
Written by Bobby Crawford March, 2016
Edited April 19, 2016
==================================================
=============DASM Dictionary Library==============

The dictionary library is used to build hash tables for O(n) worst case data lookup.
*/

//Calculate a hash value.
unsigned int _hash(char* input){

	unsigned int hashVal = 0;
	int i = 0;

	while(input[i++])
		hashVal += (input[i - 1] * i);

	return hashVal;


}



//Create a new hash table dictionary.
dictionary* _createDictionary(unsigned int startSize){

	if(!startSize)
		return 0;

	dictionary* nt = (dictionary*)malloc(sizeof(dictionary));

	nt->total = 0;
	nt->size = startSize;

	nt->table = (dictEntry*)malloc(sizeof(dictEntry) * startSize);
	memset(nt->table, 0, startSize);

	return nt;

}



//Destroy a hash table dictionary.
unsigned short _destroyDictionary(dictionary* source){

	if(!source)
		return 0;

	if(source->table)
		free(source->table);

	free(source);

	return 1;

}

void expandDictionary(dictionary* source){

	int i, total;

	dictionary* nt;

	if(!source)
		return;

	total = source->size;

	nt = _createDictionary(source->size * 2);

	for(i = 0; i < total; i++){

		if(source->table[i].hashVal)
			_insert(nt, source->table[i].hashVal, source->table[i].data);

	}

	//Perform the swap..
	source->total = nt->total;
	source->size = nt->size;

	free(source->table);
	source->table = nt->table;
	free(nt);


}

//Insert an item into the hash table.
unsigned short _insert(dictionary* source, unsigned int hashVal, void* data){

	int i, size;

	if(!source)
		return 0;

	size = source->size;
	i = hashVal % source->size;

	//No room... Expand the hash table.
	if(source->total == size)
		expandDictionary(source);

	
	//Check if the first mapped address is available.
	if(source->table[i].hashVal){

		while(source->table[i - 1].hashVal)			
			i = (i % size) + 1;
		
		i--;

	}

	//Set the value.
	source->table[i].hashVal = hashVal;
	source->table[i].data = data;
	source->total++;

	return 1;


}

//Pull an item from the dictionary.
void* _lookup(dictionary* source, unsigned int hashVal){

	int i, j, size;

	i = hashVal % source->size;
	size = source->size;
	j = 0;

	//Not in the directly mapped index? It doesn't exist!
	if(!source->table[i].hashVal)
		return 0;

	if(source->table[i].hashVal != hashVal){

		while(source->table[i - 1].hashVal != hashVal && j++ < size)
			i = (i % size) + 1;

		i--;

		if(j >= size)
			return 0;

	}

	return source->table[i].data;

}

//Remove an item from the dictionary.
unsigned short _remove(dictionary* source, unsigned int hashVal){

	int i, total;

	dictionary* nt;

	if(!source)
		return;

	total = source->size;

	nt = _createDictionary(source->size);

	for(i = 0; i < total; i++){

		if(source->table[i].hashVal && source->table[i].hashVal != hashVal)
			_insert(nt, source->table[i].hashVal, source->table[i].data);

		else if(source->table[i].hashVal == hashVal && source->table[i].data)
			free(source->table[i].data);

	}

	//Perform the swap..
	source->total = nt->total;
	source->size = nt->size;

	free(source->table);
	source->table = nt->table;
	free(nt);


}