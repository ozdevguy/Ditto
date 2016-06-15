//The ditto_functionPoolGen class is responsible for creating, maintaining, and populating a hash table of program function - location pairs.

struct fobject{
	char* name;
	long location;
};

struct fpool{
	int size;
	fobject *pool;
};

class ditto_functionPoolGen{
private:
	char initialized;
	fpool functionPool;

	//This function calculates the hash value of the given string.
	int getHashVal(char* string){
		int value, i;
		value = 0;
		i = 1;

		//Calculate the hash value of a given string.
		while(string[i - 1] != '\0' && i < 100000){
			value += string[i - 1] * i;
			i++;
		}
		
		//Return the value to the calling function.
		return value;
	}

	//This function finds a position within the function pool for the given function reference object.
	int findPos(char* string){
		int hashVal;
		long j;

		//Check to ensure initialization.
		if(initialized != 1)
			return -1;

		//Get the initial hash value.
		hashVal = getHashVal(string);

		//Set up our quadratic equation.
		j = 2;

		//Find the positon.
		while(functionPool.pool[(hashVal + j) % functionPool.size].name != NULL)
			j *= j;

		//Return the correct position.
		return (hashVal + j) % functionPool.size;
	}

	//This function locates the location of a desired function reference object.
	int locateObj(char* name,fobject **object){
		ditto_compTools tools;
		int hashVal;
		long j;

		//Check to ensure initialization.
		if(initialized != 1){
			return -1;
		}

		//Get the initial hash value.
		hashVal = getHashVal(name);

		//Set up our quadratic equation.
		j = 2;

		//Find the positon.
		while(functionPool.pool[(hashVal + j) % functionPool.size].name != NULL){

			if(tools.fullstrcmp(functionPool.pool[(hashVal + j) % functionPool.size].name,name)){

				//Set the object pointer to the found object.
				*object = &functionPool.pool[(hashVal + j) % functionPool.size];
				return 1;
			}

			j *= j;
		}
		return 0;
	}

public:

	//This function initializes the function pool for incoming function references.
	int initializePool(int size){
		initialized = 0;

		//Set a size limit of 100000 variables. 
		if(size > 100000){
			return 0;
		}

		//Set the data pool size.
		functionPool.size = size;

		//Create the pool.
		if(!(functionPool.pool = (fobject*)malloc(sizeof(fobject) * size))) //MEMORY ALLOCATION
			return 0;

		//Set the initialization variable to true, indicating that the pool has been initialized.
		initialized = 1;
		return 1;
	}

	//This function creates a function reference in the hash table.
	int put(char* name, long location){

		int i, position, nameSize;

		//Create a new tools object.
		ditto_compTools tools;

		//Get the size of the function name string.
		nameSize = tools.strsize(name);

		//Get the position fobjecr the function.
		position = findPos(name);

		//Set a pointer to the required fobject.
		fobject *object = &(functionPool.pool[position]);

		//Allocate the appropriate amount of memory for the name string.
		object->name = (char*)malloc(nameSize + 1); //MEMORY ALLOCATION

		//Copy the name string to the function object.
		for(i = 0; i < nameSize; i++)
			object->name[i] = name[i];
		object->name[i] = '\0';

		//Set the function reference.
		object->location = location;

		return 1;

	}

	//This function pulls a function reference from the function hash table.
	long get(char* name){
		fobject *object;

		//Locate the function reference object.
		if(locateObj(name,&object))
			return object->location;

		//Cannot find the function reference!
		return -1;
	}

	//Clean up the memory used by the pool.
	void cleanup(){
		int i;

		//Clear all memory used by the function names.
		for(i = 0; i < functionPool.size; i++)
			delete(functionPool.pool[i].name);

		//Clear all memory used by the pool.
		delete(functionPool.pool);
	}

};