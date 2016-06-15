#include <compiler.h>

int main(int argc, char* argv[]){
	char name[] = "MyLongVariableOne";
	char val[] = "Hello, my name is Bobby!";
	char num[] = "6.50";

	char val2[] = "3.141529";
	char name2[] = "MyDoubleVar";

	char testFunction[] = "testFunction";

	//Test the put and get functions...
	short *type;
	char *value;
	int *size;
	long location;
	long location2;

	ditto_compTools tools;

	ditto_dataPoolGen dataPool;
	dataPool.initializePool(5000);
	dataPool.put(5,name,val);
	dataPool.put(4,name2,num);
	dataPool.get(name,&location,&type,&size,&value);

	std::cout << "The location for this first piece of data is: \n" << location << "\n";
	std::cout << value << "\n";
	std::cout << "\nSize: " << *size << " Type: " << *type << "\n";
	dataPool.get(name2,&location2,&type,&size,&value);
	double test = tools.stringToDouble(value,9);
	std::cout << "\nDouble: " << test << "\n";	
	dataPool.cleanup();


	ditto_functionPoolGen functionPool;
	functionPool.initializePool(500);
	functionPool.put(testFunction,264);
	std::cout << "\nFunction Location: " << functionPool.get(testFunction) << "\n";
	functionPool.cleanup();

	short type2;
	//long location2;
	short scope;
	char* name3;
	char stackName[] = "function1";
	ditto_locStack stack;

	stack.push(1,25);
	stack.push(2,26,stackName);
	stack.push(3,27);
	stack.listStack();

	stack.pop(&type2,&location2,&name3,&scope);

	std::cout << "\nPopped: " << type2 << " " << location2 << "\n";
	stack.listStack();

	stack.pop(&type2,&location2,&name3,&scope);

	std::cout << "\nPopped: " << type2 << " " << location2 << "\n";
	stack.listStack();


	stack.peek(&type2,&location2,&name3,&scope);

	std::cout << "\nPopped: " << type2 << " " << location2 << " " << scope << "\n";
	stack.push(45,890);
	stack.listStack();

	stack.push(450,890);
	stack.listStack();
	char newVal[12];
	char* doubString;

	doubString = tools.doubleToString(4.56);

	int i = 0;

	while(doubString[i] != '\0'){
		newVal[i] = doubString[i];
		i++;
	}
	newVal[i] = '\0';

	char newVal2[] = "21.25601";

	std::cout << "\nDouble: " << tools.stringToDouble(newVal) + tools.stringToDouble(newVal2) << "\n";

	ditto_instructionGen instructions;
	instructions.setup();
	std::cout << "\nUsage: " << instructions.getUsage() << "\n";

	char varName[] = "myFirstMainVar";
	char varName2[] = "mySecondMainVar";
	char varValue[] = "256.058";

	instructions.store(5, varName, varValue);
	instructions.store(4, varName2, varValue);
	
	instructions.get(varName,1);
	instructions.get(varName2,2);

	instructions.registerDump();



	instructions.cleanup();

	return 1;
}