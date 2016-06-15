/*
This file contains the ditto_locStack (Location Reference Stack) class. This class is responsible for generating, modifying, and maintaining the
Location Reference Stack, which in turn keeps track of individual blocks of code by storing pointers to critical regions (functions, conditionals, loops, etc).
*/

/*
The robject struct provides a data structure for identifying code blocks. The variables are as follows:

name = Name of the code block (if this isn't NULL, it's the name of a class or function)
type = The type of block (function, conditional, etc...)
scope = The scope of whatever is in the block.
location = The location of the leading instruction for the block in the instruction array.
prev = The next object on the stack.
*/

struct robject{
	char* name;
	short type;
	short scope;
	long location;
	robject* prev;
};

struct rstack{
	robject* first;
	robject* last;
};

class ditto_locStack{
	private:
		rstack stack;

		int emptyStack(){
			if(!stack.first){
				return 1;
			}
			return 0;
		}

	public:
		ditto_locStack(){
			stack.first = NULL;
			stack.last = NULL;
		}

		int push(short type, long location, char* name = NULL, short scope = 0){
			int nameSize, i;
			robject *object;

			//Create a new tools object.
			ditto_compTools tools;

			//Allocate a new stack object.
			object = (robject*)malloc(sizeof(robject)); //MEMORY ALLOCATION.

			if(emptyStack()){
				stack.first = object;
				stack.last = object;
				object->prev = NULL;
			}
			else{
				object->prev = stack.last;
				stack.last = object;
			}

			object->type = type;
			object->scope = scope;
			object->location = location;
			object->name = NULL;

			//This block has a name associated with it.
			if(name){
				nameSize = tools.strsize(name);
				object->name = (char*)malloc(nameSize + 1);
				for(i = 0; i < nameSize; i++)
					object->name[i] = name[i];
				object->name[i] = '\0';
			}

			return 1;
		}

		int pop(short* type, long* location, char** name, short* scope){
			robject *prev;

			if(emptyStack())
				return 0;

			*type = stack.last->type;
			*name = stack.last->name;
			*scope = stack.last->scope;
			*location = stack.last->location;

			if(stack.last->prev){
				prev = stack.last->prev;
				if(stack.last->name)
					free(stack.last->name);
				free(stack.last);
				stack.last = prev;
			}
			else{
				if(stack.last->name)
					free(stack.last->name);
				free(stack.last);
				stack.first = NULL;
				stack.last = NULL;
			}

			return 1;

		}

		int peek(short* type, long* location, char** name, short* scope){

			if(emptyStack())
				return 0;

			*type = stack.last->type;
			*name = stack.last->name;
			*scope = stack.last->scope;
			*location = stack.last->location;

			return 1;
		}


		//List the stack contents.
		int listStack(){

			robject *object;
			object = stack.last;
			if(emptyStack())
				return 0;

			while(object->prev != NULL){
				std::cout << "\nType: " << object->type << " Location: " << object->location;
				if(object->name)
					std::cout << " Name: " << object->name;
				std::cout << "\n";
				object = object->prev;
			}
				std::cout << "\nType: " << object->type << " Location: " << object->location;
				if(object->name)
					std::cout << " Name: " << object->name;
				std::cout << "\n";
			return 1;
		}

};