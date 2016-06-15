/*
DATA TYPES (var hash table)

0 = char
1 = short
2 = int
3 = long
4 = double
5 = string
6 = void

BLOCK TYPES (Location Reference Stack)

0 = function
1 = if
2 = else if
3 = else
4 = switch
5 = while
6 = for
7 = foreach

INSTRUCTIONS

0 = GET [variable name] [register] = Move a value from the memory table into the appropriate psuedo register.
1 = PUT [variable name] [register] = Put a value in the given psuedo register back into memory at the given location.
2 = ADD [variable name] [register] = Add a value from the memory table to a value in the given psuedo register.
3 = SUB [variable name] [register] = Subtract a value from the memory table from the value in the given psuedo register.
4 = DIV [variable name] [register] = Divide a value from the memory table by the value in the given psuedo register.
5 = MUL [variable name] [register] = Multiply a value from the memory table by the value in the given psuedo register.
6 = FNC [function name] = Jump to the start of a given function.
7 = JMP [location] = Jump to a given location.
8 = FOR [numeric value] = Create a for loop by loading the given numeric value into the counter psuedo register.
9 = MOO [variable name] [output interrupt identifier] = Output something in memory to the function indicated by the given identifier.
10 = ROO [register] [output interrupt identifier] = Output something in a psuedo register to the function indicated by the given identifier.


*/

/*
class ditto_dataType{
private:
	//Convert the given data to an integer.
	void* convToInt(char* data){

	}

	void* convToDouble(char* data){

	}
	void* convToLong(char* data){

	}
	void* convToShort(char* data){

	}
	void* convToString(char* data){

	}
public:
	void* convert(char type, char* data){

	}

};
*/