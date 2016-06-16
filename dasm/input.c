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

input.c

This file contains the functions that manage information about open files.

*/

//Create a new input descriptor.
input_descriptor* _input_create_descriptor(){

	input_descriptor* id;

	id = (input_descriptor*)malloc(sizeof(input_descriptor));

	id->fnum = 0;
	id->fp = 0;

	return id;

}

//Opens a the specified file and adds it to the current input descriptor object.
unsigned short _input_add_open(input_descriptor* input, char* name){

	//Get a file object for the new file to be opened.
	FILE* nf = fopen(name, "r");

	if(!nf)
		_dasm_error_file_nonexistant(name);

	file_descriptor* nfp = (file_descriptor*)malloc(sizeof(file_descriptor));

	nfp->fp = nf;
	nfp->line = 0;
	nfp->next = 0;

	if(!input->fp){

		input->fp = nfp;
		input->fnum = 1;

	}
	else{

		file_descriptor* fd = input->fp;

		//Find the last file descriptor.
		while(fd->next)
			fd = fd->next;

		fd->next = nfp;

	}

	input->fnum++;
	input->last = nfp;

	return 1;

}

//Gets the current line in the top file.
fline* _input_get_line(input_descriptor* input){

	char line[100];

	

}


//Cleans up all inputs.
void _input_cleanup(){


}

