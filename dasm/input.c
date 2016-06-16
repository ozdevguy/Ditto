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

fline* _input_get_line(input_descriptor*);


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


//Cleans up all inputs.
static void input_file_finished(input_descriptor* input){

	//TODO: ADD METADATA...

	file_descriptor* desc;

	desc = input->fp;

	if(!desc->next){

		fclose(desc->fp);
		free(desc->fname);
		free(desc);

		input->last = 0;
		input->fp = 0;
		input->fnum--;

		return;

	}
	
	while(desc->next != input->last)
		desc = desc->next;

	fclose(desc->next->fp);
	free(desc->next->fname);
	free(desc->next);

	desc->next = 0;
	input->last = desc;
	input->fnum--;


}

void _input_cleanup(input_descriptor* input){

	free(input);

}

void _input_destroy_line(fline* line){

	if(!line)
		return;

	free(line->line);
	free(line);

}

//Gets the current line in the top file.
fline* _input_get_line(input_descriptor* input){


	char line[100];
	int i = 0;
	int j;
	int character; 

	bool first_index = false;
	bool space = false;

	//Make sure we clear this out before starting!
	memset(line, 0, 100);

	//Get the current top-level file descriptor.
	file_descriptor* fd = input->last;

	//If the top level file descriptor is null, there are no open files, so return 0.
	if(!fd)
		return 0;

	//Get the top level file pointer.
	FILE* fp = fd->fp;

	//Read the characters into the linebuffer until a newline character is encountered...
	while((character = getc(fp)) != 10 && i < 100){

		//This file is finished.
		if(character == EOF)
			break;

		//Don't start adding anything to the line buffer until we hit the first non-space character.
		if(!first_index){

			if(character != 32 && character != 9){

				first_index = true;
				line[i++] = (char)character;

			}

		}
		else{

			//If this is the first space after a word, add it to the buffer.
			if(!space && character == 32){

				space = true;
				line[i++] = (char)character;

			}

			//Don't keep spaces after commas.
			else if(character == 44){

				space = true;
				line[i++] = (char)character;

			}

			//If this is part of a word or symbol, add it to the buffer.
			else if(character != 32){

				space = false;
				line[i++] = (char)character;

			}

			//Any extra spaces are kept out of the buffer.

		}
	}

	//If the line buffer is empty, and yet we made it this far, this line was simply either a newline, or a bunch of spaces and a newline.
	//Go ahead and get the next line.
	if(line[0] == 0)
		return _input_get_line(input);

	//Increase the line count for this file.
	fd->line++;

	//Create a new line object.
	fline* fl = (fline*)malloc(sizeof(fline));

	//Create a char array for the line.
	fl->line = (char*)malloc(i);

	//Copy over the string.
	for(j = 0; j < i; j++)
		fl->line[j] = line[j];

	//If the last character to be scanned was an EOF (end of file), finish off this file.
	if(character == EOF)
		input_file_finished(input);

	return fl;


}



