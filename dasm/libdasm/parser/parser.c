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

parser.c

This file contains the functions that parse the assembly input.

*/

void _parse_global_line(fline* line){

	printf("Global Line: %s\n", line->line);

}

void _parse_data_line(fline* line){


}


void _parser_begin(char* ifpath){

	//Create a new tracker.
	global_tracker = _tracker_create();

	//Create a new input descriptor.
	input_descriptor* id = _input_create_descriptor();
	global_tracker->input_desc = id;

	//Add the base input file to the input descriptor.
	_input_add_open(id, ifpath);

	//Get the first line of input.
	fline* ln = _input_get_line(id);

	while(ln){

		if(ln->line[0] != '#'){ //Skip comments...

			switch(global_tracker->section_current){

				case INPUT_SECTION_GLOBAL:
					_parse_global_line(ln);

				case INPUT_SECTION_DATA:
					_parse_data_line(ln);

				case INPUT_SECTION_BSS:
					_parse_data_line(ln);

				case INPUT_SECTION_TEXT:
					_parse_data_text(ln);

			}

		}

		_input_destroy_line(ln);

		ln = _input_get_line(id);

	}


}



