/*
This file contains the ditto_instruction class, which is responsible for storing instructions in the instruction array, which is the primary
storage method for instructions.
*/

//The instruction struct actually stores an instruction.

struct instruction{
	short instruction;
	char arg1[30];
	char arg2[30];
	short reg;
};

struct prog{
	instruction* data;
	long size;
};

class ditto_instructionGen{
private:

	//The program container.
	prog program;

	//Memory usage.
	long memUsage;

	//Tools object.
	ditto_compTools tools;

	//Memory data pool.
	ditto_dataPoolGen varPool;

	//Function reference table.
	ditto_functionPoolGen functionPool;

	//Location/reference stack.
	ditto_locStack stack;

	//Psuedo Registers.
	int i1;
	int i2;
	int i3;

	long l1;
	long l2;
	long l3;

	short s1;
	short s2;
	short s3;

	char c1;
	char c2;
	char c3;

	char* st1;
	char* st2;
	char* st3;

	double d1;
	double d2;
	double d3;

	//Scope identifier.
	char* scope;
	short scopeSize;

	//This function places a value into the appropriate psuedo register (based on type).
	/*
	0 = char
	1 = short
	2 = int
	3 = long
	4 = double
	5 = string
	6 = void
	*/
	int typePlace(short* type, char* value, int* size, short reg = 0){
		//if(!reg){
			if(*type == 0){
				c1 = *value;
				return 1;
			}
			if(*type == 1){
				s1 = tools.stringToInt(value,*size);
				return 1;
			}
			if(*type == 2){
				i1 = tools.stringToInt(value,*size);
				return 1;
			}
			if(*type == 3){
				l1 = tools.stringToInt(value,*size);
			}
			if(*type == 4){
				d1 = tools.stringToDouble(value,*size);
			}
			if(*type == 5){
				st1 = value;
				return 1;
			}
			return 0;
		//}
		//return 0;
	}

public:

	int setup(long size = 32000){
		program.data = (instruction*)malloc(sizeof(instruction) * 32000); //MEMORY ALLOCATION.

		//Update memory usage.
		memUsage = sizeof(instruction) * 32000;

		varPool.initializePool(500);
		functionPool.initializePool(500);

		return 1;
	}

	int getUsage(){
		return memUsage;
	}

	//Store a string.
	int store(int type, char* name, char* value){
		varPool.put(type,name,value);
		std::cout << "\nSuccess!\n";
		return 1;
	}

	//Get a value from memory, and move it into a register.
	int get(char* name, short reg){
		short *type;
		char* value;
		int *size;
		long location;
		if(varPool.get(name, &location, &type, &size, &value)){
			if(typePlace(type,value,size,reg))
				return 1;
			return 0;
		}
		return 0;
	}

	void registerDump(){
		std::cout << "\n=== REGISTER DUMP ===\n";
		std::cout << "\n=== Reg i1: " << i1 << " ===\n";
		std::cout << "\n=== Reg i2: " << i2 << " ===\n";
		std::cout << "\n=== Reg i3: " << i3 << " ===\n";
		std::cout << "\n=== Reg l1: " << l1 << " ===\n";
		std::cout << "\n=== Reg l2: " << l2 << " ===\n";
		std::cout << "\n=== Reg l3: " << l3 << " ===\n";
		std::cout << "\n=== Reg s1: " << s1 << " ===\n";
		std::cout << "\n=== Reg s2: " << s2 << " ===\n";
		std::cout << "\n=== Reg s3: " << s3 << " ===\n";
		std::cout << "\n=== Reg c1: " << c1 << " ===\n";
		std::cout << "\n=== Reg c2: " << c2 << " ===\n";
		std::cout << "\n=== Reg c3: " << c3 << " ===\n";
		std::cout << "\n=== Reg st1: " << st1 << " ===\n";
		std::cout << "\n=== Reg st2: " << st2 << " ===\n";
		std::cout << "\n=== Reg st3: " << st3 << " ===\n";
		std::cout << "\n=== Reg d1: " << d1 + 1 << " ===\n";
		std::cout << "\n=== Reg d2: " << d2 << " ===\n";
		std::cout << "\n=== Reg d3: " << d3 << " ===\n";

	}

	void cleanup(){
		free(program.data);
	}

};