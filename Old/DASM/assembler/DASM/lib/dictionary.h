/*
The Ditto Virtual Machine | Ditto Assembler (DASM) 
Written by Bobby Crawford March, 2016
Edited March, 2016
==================================================
=============DASM Dictionary Library==============

The dictionary library is used to build hash tables for O(n) worst case data lookup.
*/

//Individual dictionary item.
typedef struct {

	unsigned int hashVal;
	void* data;

} dictEntry;


//Dictionary object.
typedef struct{

	dictEntry* table;
	unsigned int total;
	unsigned int size;

} dictionary;


//Generate a hash code for an object.
unsigned int _hash(char*);

//Insert an item into the dictionary.
unsigned short _insert(dictionary*, unsigned int, void*);

//Create a new dictionary.
dictionary* _createDictionary(unsigned int);

//Destroy a dictionary.
unsigned short _destroyDictionary(dictionary*);

//Look for an item in the dictionary.
void* _lookup(dictionary*, unsigned int);

//Remove an item from the dictionary.
unsigned short _remove(dictionary*, unsigned int);



