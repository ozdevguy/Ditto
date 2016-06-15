//The ditto_poolGen class is responsible for setting up the memory pool for compiled variables, which exists in the form of a hash table.


namespace __ditto_compiler{


//The dobject struct contains information about a variable.
struct dobject{
	char* name;
	long size;
	long memoryLocation;
};

//The dpool struct contains both a pointer to the actual data pool hash table, but also critical information about the pool, such as its size.
struct dpool{
	int size;
	dobject *pool;
};

class dataHash{

private:

	char initialized;
	dpool dataPool;
	compTools tools;
	staticMemPool memory;

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

	//This function finds a position within the data pool for the given variable.
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
		while(dataPool.pool[(hashVal + j) % dataPool.size].name != NULL)
			j *= j;

		//Return the correct position.
		return (hashVal + j) % dataPool.size;
	}

	//This function locates the location of a desired object.
	int locateObj(char* name, long* location){
		int hashVal;
		long j;

		//Check to ensure initialization.
		if(initialized != 1)
			return -1;

		//Get the initial hash value.
		hashVal = getHashVal(name);

		//Set up our quadratic equation.
		j = 2;

		//Find the positon.
		while(dataPool.pool[(hashVal + j) % dataPool.size].name != NULL){

			if(tools.fullstrcmp(dataPool.pool[(hashVal + j) % dataPool.size].name,name)){

				//Set the location object to the actual location.
				*location = &dataPool.pool[(hashVal + j) % dataPool.size].memoryLocation;

				return 1;
			}

			j *= j;
		}
		return 0;
	}

public:
	//This function initializes the data pool for incoming variables.
	int initializePool(int size){
		initialized = 0;

		//Set a size limit of 100000 variables. 
		if(size > 100000){
			return 0;
		}

		//Set the data pool size.
		dataPool.size = size;

		//Create the pool.
		if(!(dataPool.pool = (dobject*)malloc(sizeof(dobject) * size))) //MEMORY ALLOCATION
			return 0;

		//Set the initialization variable to true, indicating that the pool has been initialized.
		initialized = 1;
		return 1;
	}

	//This operation places a value into the data pool.
	void put(short type, long size, char* name, void* data){
		int nameSize, pos;
		int i = 0;

		//Get the size of the name string.
		nameSize = tools.strsize(name);


		//First, we need to find the position for the object.
		pos = findPos(name);

		//Now, let's set a pointer to the hash table object for the data.
		dobject *object = &(dataPool.pool[pos]);

		//Set the size of the data...
		object->size = size;

		//Set the data type...
		object->type = type;

		//Set the value of the object name.
		object->name = (char*)malloc(nameSize + 1); //MEMORY ALLOCATION

		//Copy the contents of the name buffer to the object's memory.
		for(i = 0; i < nameSize; i++)
			object->name[i] = name[i];
		object->name[i] = '\0';

		//Set the value of the data.
		object->data = (char*)malloc(size + 1); //MEMORY ALLOCATION

		//Copy the contents of the data buffer to the object's memory.
		for(i = 0; i < size; i++)
			object->data[i] = data[i];
		object->data[i] = '\0';
	}

	//This function gets the data from an object.
	int get(char* name, long *location, short **type, long **size, int **data){
		if(locateObj(name,location)){
			*value = temp->data;
			*type = &temp->type;
			*size = &temp->size;
			return 1;
		}

		return 0;
	}

	//This function performs cleanup, freeing the memory of all allocated objects.
	void cleanup(){
		int i;

		//Clean up each pool object.
		for(i = 0; i < dataPool.size; i++){
			free(dataPool.pool[i].name);
		}

		//Release the pool.
		free(dataPool.pool);
	}


};

};
