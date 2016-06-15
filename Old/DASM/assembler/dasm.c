#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libdasm.h"


char* outputfile;
unsigned short outputfile_strsz = 0;

char* inputfile;
unsigned short inputfile_strsz = 0;



int parseArg(int argc, char* argv[]){

	int i, j;

	for(i = 1; i < argc; i++){

		//Do not perform linking...
		if(!strcmp(argv[i], "-l")){

			printf("Perform automatic linking (build executable)...\n");
		
		}

		//Set output file name.
		else if(!strcmp(argv[i], "-o") && i < (argc - 1)){

			j = 0;
			i++;

			while(argv[i][j++])
				outputfile_strsz++;

			outputfile = (char*)malloc(outputfile_strsz);

			for(j = 0; j < outputfile_strsz; j++)
				outputfile[j] = argv[i][j];


		}

		//Set input file name.
		else{

			printf("Got input file...\n");

			j = 0;

			while(argv[i][j++])
				inputfile_strsz++;

			inputfile = (char*)malloc(inputfile_strsz);

			for(j = 0; j < inputfile_strsz; j++)
				inputfile[j] = argv[i][j];

		}

	}

	return 0;
}

int main(int argc, char* argv[]){

	//First things first, we need to setup the assembler based on the given arguments.

	parseArg(argc, argv);

	printf("Input file: %s\nOutput File: %s\n\n", inputfile, outputfile);

	return 0;
}