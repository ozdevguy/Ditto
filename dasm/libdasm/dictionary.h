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

dictionary.h

This is the header file for the dictionary functions, which allow the program to build a fast lookup dictionary of items via the use of a
hash table.

*/

#include <string.h>

#include "libs/dictionaryStructures.c"
#include "libs/dictionary.c"


//Calculate a unique dictionary hash value.
unsigned int _dictionary_hash(char*);

//Create a new dictionary _create_dictionary(starting size (dictionary entries)) -> Returns a new dictionary object.
dictionary* _dictionary_create(unsigned int);

//Destroy a dictionary _dictionary_destroy(dictionary)
unsigned short _dictionary_destroy(dictionary*);

//Insert an item into the dictionary _dictionary_insert(dictionary, object pointer, label string)
unsigned short _dictionary_insert(dictionary*, void*, unsigned int);

//Look for an item in the dictionary _dictionary_lookup
void* _dictionary_lookup(dictionary*, unsigned int);

//Remove an item from the dictionary.
unsigned short _dictionary_remove(dictionary*, unsigned int);



