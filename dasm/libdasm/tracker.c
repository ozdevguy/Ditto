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

tracker.c

This file contains the structures and variables which provide us with a way to globally track the assembly
process.

*/

//Enumeration of values relating to different assembly input sections.
enum {INPUT_SECTION_GLOBAL, INPUT_SECTION_BSS, INPUT_SECTION_DATA, INPUT_SECTION_TEXT};

typedef struct {

	//Current section.
	int section_current;

	//Section parsing indicators.
	bool section_global_parsed;
	bool section_data_parsed;
	bool section_bss_parsed;
	bool section_text_parsed;

	//The current input descriptor.
	input_descriptor* input_desc;


} dasm_tracker;


dasm_tracker* global_tracker;


dasm_tracker* _tracker_create(){

	dasm_tracker* nt;

	nt = (dasm_tracker*)malloc(sizeof(dasm_tracker));
	nt->section_current = INPUT_SECTION_GLOBAL;
	nt->section_global_parsed = false;
	nt->section_data_parsed = false;
	nt->section_bss_parsed = false;
	nt->section_text_parsed = false;

	return nt;
}

void _tracker_destroy(dasm_tracker* tracker){

	free(tracker);

}