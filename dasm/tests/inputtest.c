
#include "../libdasm.h"


//TEST THE INPUT MANAGEMENT OPERATIONS...

int main(){

	//Create a new input descriptor...
	input_descriptor* id = _input_create_descriptor();

	//Hand the first file to the input manager.
	_input_add_open(id, "inputmngr_test.txt");

	//Get our first line...
	fline* ln = _input_get_line(id);

	printf("%s\n", ln->line);

	while(ln = _input_get_line(id)){

		//No more lines...
		if(!ln)
			break;

		if(ln->line[0] == '*')
			_input_add_open(id, "inputmngr_test2.txt");

		else
			printf("%s\n", ln->line);


	}
	//Clean things up...
	_input_cleanup(id);

	return 0;
}