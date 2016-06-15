/*
Compiler Header File
*/

//Set up needed data types.
namespace __ditto_compiler{

	//This enumeration allows us to represent types with a familiar name.
	enum {
		BYTE,
		CHARACTER,
		UNSIGNED_SHORT,
		SHORT,
		UNSIGNED_INTEGER,
		INTEGER,
		UNSIGNED_LONG,
		LONG,
		UNSIGNED_FLOAT,
		FLOAT,
		DOUBLE,
		LONG_DOUBLE,
		POINTER
	};
	
	typedef unsigned char byte;
};


#include <stdlib.h>
#include <iostream>
#include "base/errorParser.cpp"
#include "base/errorType.cpp"
#include "base/tools.cpp"
#include "base/dataPool.cpp"
//#include "base/dataHash.cpp"
#include "base/functionHash.cpp"
#include "base/locationStack.cpp"
