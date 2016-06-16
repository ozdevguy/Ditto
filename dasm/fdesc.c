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

fdesc.c

This file contains the structures for maintaining data about open files.

*/


typedef struct {

	//Standard file object.
	FILE* fp;

	//File name.
	char* fname;

	//Line number.
	unsigned int line;

	//Next file descriptor.
	file_descriptor* next;

} file_descriptor;


//Input descriptor structure.
typedef struct {

	//A linked list of file descriptors!
	file_descriptor* fp;

	//The last file descriptor.
	file_descriptor* last;

	//Total number of file descriptor pointers.
	unsigned int fnum;

} input_descriptor;


//Current line.
typedef struct {

	//Line string.
	char* line;

	//Line length.
	unsigned short length;

} fline;

