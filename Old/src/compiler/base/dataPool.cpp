/*
This file contains the ditto_datapool class, which is responsible for setting up and maintaining the Ditto variable data pool, which in turn stores all
static variables linearly in an array.
*/

namespace __ditto_compiler{

//The memory struct contains critical information about the memory pool used by the compiler.
struct memory{
	int size;
	byte* memory;
};

//The staticMemPool class is responsible for creating, maintaining, allocating, and resizing the static memory pool, which stores stack variables.
class staticMemPool{
private:

	//Set up a tools object.
	compTools tools;

	//The setup variable indicates whether or not the memory pool has been successfully initialized.
	short initialized;

	//Create a new memory pool object.
	memory pool;

	//Current memory location.
	int locationPointer;	

	//This function creates the variable memory pool.
	int createPool(){

		if(pool.size > 3){
			if((pool.memory = (byte*)malloc(pool.size))){ //MEMORY ALLOCATION.
				return 1;
			}
			//ERROR
			return 0;
		}
		//ERROR
		return 0;
	}

	//Resize the memory pool should our space be exhausted.
	int resizePool(){
		byte* tempPtr;
		int i;

		if((tempPtr = (byte*)malloc((pool.size * 1.5)))){

			for(i = 0; i <= locationPointer; i++)
				tempPtr[i] = pool.memory[i];
			
			free(pool.memory);	//MEMORY FREE
			pool.memory = tempPtr;
			pool.size *= 1.5;
		}
		//ERROR
		return 0;
	}

	//Set the header for a new block of memory. Return the location of the data portion.
	int setHeader(short type, long allocationSize){
		unsigned short temp;
		byte init;
		short i;

		//Set the first nibble of the first byte as the type.
		init = (type << 4);

		//Set the appropirate number of bytes to store the length.
		if(allocationSize < 256)
			temp = 1;
		else if(allocationSize < 65536)
			temp = 2;
		else if(allocationSize < 16777216)
			temp = 3;
		else if(allocationSize < 4294967296)
			temp = 4;
		else
			return 0;

		//Add the length flag to the second nibble of the first byte of the header.
		init += temp;

		pool.memory[locationPointer++] = init;

		//Set up the semaphore...
		pool.memory[locationPointer++] = 0;

		//Place the length into the length bytes.
		for(i = ((temp - 1) * 8); i >= 0; i -= 8)
			pool.memory[locationPointer++] = (allocationSize >> i);

		return 1;

	}

	//Check to make sure we have enough space for a new allocation, and if not, increase the size of the static memory pool.
	void checkSize(long allocationSize){
		short headerSize;

		if(allocationSize < 256)
			headerSize = 3;
		else if(allocationSize < 65536)
			headerSize = 4;
		else if(allocationSize < 16777216)
			headerSize = 5;
		else if(allocationSize < 4294967296)
			headerSize = 6;

		allocationSize += headerSize;

		while((locationPointer + allocationSize) > pool.size)
				resizePool();
	}

public:

	/*
	=========
	SEMANTICS
	=========
	*/

	//Get total size.
	long getTotalSize(){
		return locationPointer + 1;
	}

	//Print static memory contents to the screen.
	void printMem(){
		int i;
		for(i = 0; i <= locationPointer; i++)
			std::cout << "\nByte Location: " << i << " | Value: " << pool.memory[i] << "\n";
	}

	//This function cleans up the memory after the compilation process.
	void cleanup(){
		free(pool.memory);
	}

	//This function sets up the memory pool.
	int setup(int poolSize){
		initialized = 0;

		if(poolSize > 2){
			pool.size = poolSize;
			if(createPool()){
				locationPointer = 0;
				initialized = 1;
				return 1;
			}
			return 0;
		}

		return 0;
	}

	/*
	=================
	MEMORY ALLOCATION
	=================
	*/

	//This function allocates space for a single character.
	long allocateChar(char* character){
		long location;
		
		location = locationPointer;
		short headerSize = 0;

		if(initialized ){
			
			checkSize(1);
			if(setHeader(CHARACTER,1)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				pool.memory[locationPointer++] = (byte)(*character);

				locationPointer += headerSize;

				return location;
			}
		}

		return -1;
	}

	//This function allocates space for a string of characters.
	long allocateString(int allocationSize, int dataSize, char* data = NULL){
		long location;
		int i, j;
		
		location = locationPointer;
		short headerSize = 0;

		if(initialized ){
			if(!allocationSize || allocationSize < dataSize)
				return -1;
			
			checkSize(allocationSize);
			if(setHeader(CHARACTER,allocationSize)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				for(i = 0; i < dataSize; i ++){
					if(data[i]){
							pool.memory[locationPointer++] = data[i];
					}
					else{
						pool.memory[locationPointer++] = 0;
					}
				}

				locationPointer += (headerSize + allocationSize - dataSize);

				return location;
			}
		}

		return -1;
	}

	//This function allocates space for a group of unsigned short data, then returns the memory location.
	long allocateUShort(unsigned long allocationSize, long dataSize, unsigned short* data = NULL){
		int i, j, location;
		
		location = locationPointer;
		short headerSize = 0;
		allocationSize *= sizeof(short);

		if(initialized ){
			if(!allocationSize || allocationSize < (dataSize * sizeof(short)))
				return -1;
			
			checkSize(allocationSize);
			if(setHeader(UNSIGNED_SHORT,allocationSize)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				for(i = 0; i < dataSize; i ++){
					if(data[i]){

						for(j = ((sizeof(short) - 1) * 8); j >= 0; j -= 8){
							pool.memory[locationPointer++] = (data[i] >> j);
						}

					}
					else{
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
					}
				}

				locationPointer += (headerSize + allocationSize - (dataSize * sizeof(short)));

				return location;
			}
		}

		return -1;
	}

	//This function allocates space for a group of signed short data, then returns the memory location.
	long allocateShort(unsigned long allocationSize, long dataSize, short* data = NULL){
		int i, j, location;
		
		location = locationPointer;
		short headerSize = 0;
		allocationSize *= sizeof(short);

		if(initialized ){
			if(!allocationSize || allocationSize < (dataSize * sizeof(short)))
				return -1;
			
			checkSize(allocationSize);
			if(setHeader(SHORT,allocationSize)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				for(i = 0; i < dataSize; i ++){
					if(data[i]){

						for(j = ((sizeof(short) - 1) * 8); j >= 0; j -= 8){
							pool.memory[locationPointer++] = (data[i] >> j);
						}

					}
					else{
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
					}
				}

				locationPointer += (headerSize + allocationSize - (dataSize * sizeof(short)));

				return location;
			}
		}

		return -1;
	}

	//This function allocates space for a group of unsigned integers, then returns the memory location.
	long allocateUInt(unsigned long allocationSize, long dataSize, unsigned int* data = NULL){
		int i, j, location;
		
		location = locationPointer;
		short headerSize = 0;
		allocationSize *= sizeof(int);

		if(initialized ){
			if(!allocationSize || allocationSize < (dataSize * sizeof(int)))
				return -1;
			
			checkSize(allocationSize);
			if(setHeader(UNSIGNED_INTEGER,allocationSize)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				for(i = 0; i < dataSize; i ++){
					if(data[i]){

						for(j = ((sizeof(int) - 1) * 8); j >= 0; j -= 8){
							pool.memory[locationPointer++] = (data[i] >> j);
						}

					}
					else{
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
					}
				}

				locationPointer += (headerSize + allocationSize - (dataSize * sizeof(int)));

				return location;
			}
		}

		return -1;
	}


	//This function allocates space for a group of signed integers, then returns the memory location.
	long allocateInt(unsigned long allocationSize, long dataSize, int* data = NULL){
		int i, j, location;
		
		location = locationPointer;
		short headerSize = 0;
		allocationSize *= sizeof(int);

		if(initialized ){
			if(!allocationSize || allocationSize < (dataSize * sizeof(int)))
				return -1;
			
			checkSize(allocationSize);
			if(setHeader(INTEGER,allocationSize)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				for(i = 0; i < dataSize; i ++){
					if(data[i]){

						for(j = ((sizeof(int) - 1) * 8); j >= 0; j -= 8){
							pool.memory[locationPointer++] = (data[i] >> j);
						}

					}
					else{
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
					}
				}

				locationPointer += (headerSize + allocationSize - (dataSize * sizeof(int)));

				return location;
			}
		}

		return -1;
	}

	//This function allocates space for a group of unsigned long values, then returns the memory location.
	long allocateULong(unsigned long allocationSize, long dataSize, unsigned long* data = NULL){
		int i, j;
		long location;
		
		location = locationPointer;
		short headerSize = 0;
		allocationSize *= sizeof(long);

		if(initialized ){
			if(!allocationSize || allocationSize < (dataSize * sizeof(long)))
				return -1;
			
			checkSize(allocationSize);
			if(setHeader(LONG,allocationSize)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				for(i = 0; i < dataSize; i ++){
					if(data[i]){

						for(j = ((sizeof(long) - 1) * 8); j >= 0; j -= 8){
							pool.memory[locationPointer++] = (data[i] >> j);
						}

					}
					else{
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
					}
				}

				locationPointer += (headerSize + allocationSize - (dataSize * sizeof(long)));

				return location;
			}
		}

		return -1;
	}


	//This function allocates space for a group of signed long values, then returns the memory location.
	long allocateLong(unsigned long allocationSize, long dataSize, long* data = NULL){
		int i, j;
		long location;
		
		location = locationPointer;
		short headerSize = 0;
		allocationSize *= sizeof(long);

		if(initialized ){
			if(!allocationSize || allocationSize < (dataSize * sizeof(long)))
				return -1;
			
			checkSize(allocationSize);
			if(setHeader(LONG,allocationSize)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				for(i = 0; i < dataSize; i ++){
					if(data[i]){
						std::cout << "\nData: " << data[i] << "\n";
						for(j = ((sizeof(long) - 1) * 8); j >= 0; j -= 8){
							pool.memory[locationPointer++] = (data[i] >> j);
						}

					}
					else{
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
						pool.memory[locationPointer++] = 0;
					}
				}

				locationPointer += (headerSize + allocationSize - (dataSize * sizeof(long)));

				return location;
			}
		}

		return -1;
	}

	


	//This function allocates space for a group of doubles.
	long allocateDouble(int allocationSize, int dataSize, double* data){
		int i, j;
		long location, rep;
		
		location = locationPointer;
		short headerSize = 0;
		allocationSize *= sizeof(long);

		if(initialized ){
			if(!allocationSize || allocationSize < (dataSize * sizeof(long)))
				return -1;
			
			checkSize(allocationSize);
			if(setHeader(INTEGER,allocationSize)){

				//Set the header size..
				headerSize = (locationPointer - location);

				//Insert the given data.
				for(i = 0; i < dataSize; i ++){
					if(data[i]){
						rep = (long)(data[i] * 1000000);
						for(j = ((sizeof(long) - 1) * 8); j >= 0; j -= 8){
							pool.memory[locationPointer++] = (rep >> j);
						}

					}
					else{
						for(j = ((sizeof(long) - 1) * 8); j >= 0; j -= 8){
							pool.memory[locationPointer++] = 0;
						}
					}
				}

				locationPointer += (headerSize + allocationSize - (dataSize * sizeof(int)));

				return location;
			}
		}

		return -1;
	}


	/*
	==========
	DATA QUERY
	==========
	*/

	//Get the explicit length of a specific group of data.
	long getLengthExplicit(int location){
		unsigned long length;
		short type, hl;

		byte temp;
		if(location < locationPointer){
			if(getHeader(location,&type,&length,&hl)){
				return length;
			}
			return -1;
		}
		return -1;
	}

	//Get the implicit length of a specific group of data.
	long getLengthImplicit(int location){
		unsigned long length;
		short type, hl;

		byte temp;
		if(location < locationPointer){
			if(getHeader(location,&type,&length,&hl)){
				switch(type){
					case CHARACTER:
						return length;
						break;
					case SHORT:
						return length / sizeof(short);
						break;
					case INTEGER:
						return length / sizeof(int);
						break;
					case DOUBLE:
						return length / sizeof(double);
						break;
					case LONG:
						return length / sizeof(long);
						break;
				}
			}
			return -1;
		}
		return -1;
	}

	//Get the header of a piece of data.
	int getHeader(long location, short* type, unsigned long* length, short* headerSize, byte* semaphore = NULL){
		byte schema, sem;
		unsigned long dataLength;
		short t, lf, hs, i;

		//Get the schema byte...
		schema = pool.memory[location++];

		//Get the data type..
		t = (schema >> 4) & 255;

		//Get the length flag.
		lf = schema & 15;

		//Get the semaphore..
		sem = pool.memory[location++];

		hs = 2 + lf;
		
		dataLength = 0;

		for(i = ((lf - 1) * 8); i >= 0; i -= 8)
			dataLength += (pool.memory[location++] << i);
		
		*type = t;
		*length = dataLength;
		//*semaphore = sem;
		*headerSize = hs;
		return 1;

	}


	/*
	=====
	STORE
	=====
	

	//Store a character.
	void storeChar(int location, char character, int offset = 0){
		if(location < locationPointer){
			if(offset < pool.memory[location + 1])
				pool.memory[location + offset + 2] = character;
		}
	}

	//Store a double.
	void storeDouble(int location, double dval, int offset = 0){
		int whole, fraction, places;
		offset *= 3;

		if(location < locationPointer){
			if((offset/3) < pool.memory[location + 1]){
				tools.breakDouble(dval,&whole,&fraction,&places);
				pool.memory[location + offset + 2] = places;
				pool.memory[location + offset + 3] = whole;
				pool.memory[location + offset + 4] = fraction;
			}
		}
	}

	//Store an integer.
	void storeInt(int location, int integer, int offset = 0){
		if(location < locationPointer){
			if(offset < pool.memory[location + 1])
				pool.memory[location + offset + 2] = integer;
		}
	}

	//Store a bool.
	void storeBool(int location, short boolean, int offset = 0){
		if(boolean > 0)
			boolean = 1;

		if(location < locationPointer){
			if(offset < pool.memory[location + 1])
				pool.memory[location + offset + 2] = boolean;
		}
	}


	/*
	================
	PULL FROM MEMORY
	================
	*/

	char pullChar(long location,long offset = 0){
		short headerSize, i;
		unsigned long dataSize, dataLoc;
		short type;

		if(location < (locationPointer + 7)){
			getHeader(location,&type,&dataSize,&headerSize);
			if(offset <= dataSize){
				dataLoc = location + headerSize + offset;
				return (char)pool.memory[dataLoc];
			}
			std::cout << "\nERROR: Stack overflow. The specified index is greater than the number of elements in the array!\n";
			return NULL;
		}
		return NULL;
	}

	//Pull an integer from memory.
	int pullInt(long location,long offset = 0){
		short headerSize, i;
		unsigned long dataSize, dataLoc;
		short type;
		int value = 0;

		//Correct the offset.
		offset *= sizeof(int);

		if(location < (locationPointer + 7)){
			getHeader(location,&type,&dataSize,&headerSize);
			if(offset <= (dataSize - sizeof(int))){
				dataLoc = location + headerSize + offset;
				for(i = ((sizeof(int) - 1) * 8); i >= 0; i -= 8)
					value += (pool.memory[dataLoc++] << i);
				return value;
			}
			std::cout << "\nERROR: Stack overflow. The specified index is greater than the number of elements in the array!\n";
			return 0;
		}
		return 0;
	}

	//Pull a long from memory.
	long pullLong(long location,long offset = 0){
		short headerSize, i;
		unsigned long dataSize, dataLoc;
		short type;
		unsigned long value = 0;

		//Correct the offset.
		offset *= sizeof(long);

		if(location < (locationPointer + 7)){
			getHeader(location,&type,&dataSize,&headerSize);
			if(offset <= (dataSize - sizeof(long))){
				dataLoc = location + headerSize + offset;
				for(i = ((sizeof(long) - 1) * 8); i >= 0; i -= 8){
					value += (pool.memory[dataLoc++] << i);
				}
				return value;
			}
			std::cout << "\nERROR: Stack overflow. The specified index is greater than the number of elements in the array!\n";
			return 0;
		}
		return 0;
	}

	//Pull a double from memory.
	double  pullDouble(long location,long offset = 0){
		short headerSize, i;
		unsigned long dataSize, dataLoc;
		short type;
		long value = 0;
		double valD = 0;

		//Correct the offset.
		offset *= sizeof(long);

		if(location < (locationPointer + 7)){
			getHeader(location,&type,&dataSize,&headerSize);
			if(offset <= (dataSize - sizeof(long))){
				dataLoc = location + headerSize + offset;
				for(i = ((sizeof(long) - 1) * 8); i >= 0; i -= 8)
					value += (pool.memory[dataLoc++] << i);
				valD = value;
				valD *= .1000000;
				std::cout << valD * .1000000;
				return valD;
			}
			std::cout << "\nERROR: Stack overflow. The specified index is greater than the number of elements in the array!\n";
			return 0;
		}
		return 0;
	}

	/*

	int getData(void** dataPointer, int** type, int** size, int location, int offset = 0){

		if(pool.memory[location]){
			if(offset >= pool.memory[location + 1]){
				//Throw index out of bounds...
				return 0;
			}
			
			*type = &(pool.memory[location++]);
			*size = &(pool.memory[location++]);
			*dataPointer = &(pool.memory[location + offset]);
			return 1;
		}
		else{
			//Throw some sort of exception for invalid memory access.
			return 0;
		}
		return 1;
	}
	*/
		
};


};
