

typedef struct{

	bool perform_linking;
	bool output_sym_tbl;
	bool crypt;
	char* output;
	char* input;
	char* link[];

} env;

env* environment;

void set_ENV(){

	environment = (env*)malloc(sizeof(env));

}


void kill_ENV(){

	free(environment);

}


void perform_linking(){

	environment->perform_linking = true;

}

void output_sym_tbl(){

	environment->output_sym_tbl = true;

}

void set_output_file(char* fname, unsigned int flength){


}

void set_input_file(char* fname, unsigned int flength){

	
}