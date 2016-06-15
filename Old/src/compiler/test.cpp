#include "compiler.h"

int main(){
	__ditto_compiler::compTools testTools;
	__ditto_compiler::staticMemPool myMem;
	myMem.setup(1024);
	/*
	char *testString = "Hello! \nHow are you today? Great, well, that's swell!";
	myMem.setup(1024);
	int strLoc = myMem.allocateString(testTools.strsize(testString),testTools.strsize(testString),testString);
	int myNewInt = 24;
	int testArr[] = {1,2,3,4,5};
	char charData[] = {'a','b','c','d','e','f'};
	double myDoubles[] = {3.141529,6.1092,2.874,92.34,999.99};
	int intLoc = myMem.allocateInt(3,1,&myNewInt);
	int doubleLocation = myMem.allocateDouble(6,5,myDoubles);
	myMem.storeDouble(doubleLocation,9.87654,3);
	int stringLocation = myMem.allocateString(6,6,charData);
	char characterZ = 'z';
	myMem.storeChar(stringLocation,characterZ,3);
	std::cout << myMem.getLength(doubleLocation);	
	for(int i = 0; i < myMem.getLength(stringLocation); i++){
		std::cout << "\n" << myMem.pullChar(stringLocation,i) << "\n";
	}
	
	for(int j = 0; j < myMem.getLength(doubleLocation); j++){
		std::cout << "\nDouble: " << myMem.pullDouble(doubleLocation,j) << "\n";
	}
	
	for(int k = 0; k < myMem.getLength(strLoc); k++){
		std::cout << myMem.pullChar(strLoc,k);
	}

	std::cout << "\nInteger: " << myMem.pullInt(intLoc) << "\n";
	
	/*	
	int* testArr2 = (int*)malloc(sizeof(int) * 2000);
	for(int i = 0; i < 2000; i++)
		testArr2[i] = i + 100;

	int location1 = myMem.storeInt(1,1,&myNewInt);
	int location2 = myMem.storeInt(5,5,testArr);
	int location3 = myMem.storeInt(10000,2000,testArr2);

	void *testVar;
	int *size;
	int *type;

	myMem.getData(&testVar,&type,&size,location1);
	myMem.getData(&testVar,&type,&size,location2);
	myMem.getData(&testVar,&type,&size,location3);

	if(*type == __ditto_compiler::INTEGER)
		std::cout << "\nThe value that has been referenced is an integer!\n";

	std::cout << "\nThe value at location 1 is: " << *((int*)(testVar)) << "\n";

	myMem.printMem();
	*/
	long testLong = 21474836784588;
	std::cout << "\n" << (testLong << 32) << "\n";
	int testInt[] = {24,32,-4,128};
	char* testString = "Hello world! This is a test of the character storing abilities of Ditto's static memory pool.\nThat will be all...";
	int testInt2 = 8675309;
	double testDouble = 3.141529;
	int location = myMem.allocateInt(20,4,testInt);
	int location2 = myMem.allocateInt(1,1,&testInt2);
	int location3 = myMem.allocateString(testTools.strsize(testString),testTools.strsize(testString),testString);
	int location4 = myMem.allocateLong(2,1,&testLong);
	int location5 = myMem.allocateInt(30,4,testInt);
	int location6 = myMem.allocateDouble(1,1,&testDouble);

	std::cout << "\nLocation2: " << location2 << "\n";
	unsigned long dataSize;
	short type;
	short headerSize;
	myMem.getHeader(location2,&type,&dataSize,&headerSize);
	std::cout << "Header Size: " << headerSize << " | Type: " << type << " | Data Size: " << dataSize << "\n";
	std::cout << "Total Size: " << myMem.getTotalSize() << "\n";
	
	std::cout << "\nValue: " << myMem.pullInt(location2);
	for(int i = 0; i < testTools.strsize(testString); i++)
		std::cout << myMem.pullChar(location3,i);

	std::cout << "\n\nLongVal: " << myMem.pullLong(location4);
	std::cout << "\n\nIntVal: " << myMem.pullInt(location5,1);
	std::cout << "\nImplicit: " << myMem.getLengthImplicit(location4) << "\n";
	std::cout << "\nExplicit: " << myMem.getLengthExplicit(location4) << "\n";
	std::cout << "\nDouble: " << myMem.pullDouble(location6) << " | Long Double: " << sizeof(long double) << "\n";

	myMem.cleanup();

	__ditto_compiler::compTools tools;
	long whole;
	long dec;
	short places;

	tools.breakDouble(-3016584.141529,&whole,&dec,&places);
	std::cout << "\nWhole: " << whole << " Decimal: " << dec << " Places: " << places << "\n";
	std::cout << "\nRebult: " << tools.rebuildDouble(whole,dec,places) << "\n";

	return 1;
}
