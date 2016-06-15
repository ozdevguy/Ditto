
class ditto_compTools{
private:
char* tempString;

public:

	ditto_compTools(){
		tempString = (char*)malloc(1); //MEMORY ALLOCATION.
	}

	//Get the size of a string.
	int strsize(char* string){
		int i = 0;
		while(string[i] != '\0' && i < 100000)
			i++;
		return i;
	}

	//Get a string up to the specified character.
	int getStringTo(char* string, char to){
		free(tempString);
		int i = 0;
		int j;
		while(string[i] != '\0' && i < 100000){
			if(string[i] == to){
				tempString = (char*)malloc(i + 1); //MEMORY ALLOCATION
				tempString[i] = '\0';
				for(j = 0; j < i; j++)
					tempString[j] = string[j];
				return 1;
			}
			i++;
		}
		return 0;
	}

	//Convert integer to string.
	char* intToString(long integer){
		int divisor = 1;
		int length = 0;
		int start = 0;
		short neg = 0;
		int digit;
		char out;
		int i;

		//Set negative flag.
		if(integer < 0){
			neg = 1;
			integer *= -1;
		}

		//Reset the temp string.
		free(tempString);

		//Get the maximum multiplier for the integer value...
		while(divisor < integer){
			divisor *= 10;
			length++;
		}
		divisor /= 10;

		//Check if negative.
		if(neg){
			start = 1;
			length += 1;
		}

		//Allocate an appropriately sized string.
		tempString = (char*)malloc(length + 1); //MEMORY ALLOCATION

		if(neg)
			tempString[0] = '-';

		//Get the ascii value of each number.
		for(i = start; i < length; i++){

			digit = integer / divisor;
			integer -= (digit * divisor);
			divisor /= 10;

			switch(digit){
				case 0:
					out = '0';
					break;
				case 1:
					out = '1';
					break;
				case 2:
					out = '2';
					break;
				case 3:
					out = '3';
					break;
				case 4:
					out = '4';
					break;
				case 5:
					out = '5';
					break;
				case 6:
					out = '6';
					break;
				case 7:
					out = '7';
					break;
				case 8:
					out = '8';
					break;
				case 9:
					out = '9';
					break;
				default:
					out = '0';
				};

				tempString[i] = out;
		}

		tempString[length] = '\0';
		return tempString;
	}

	//Convert double to string.
	char* doubleToString(long double value){
		char* fhPointer;
		char* shPointer;
		int firstHalfSize;
		int secondHalfSize = 0;
		long firstHalf = value;
		long double secondHalf = value - firstHalf;
		short addedZeros;
		int i = 0;

		if(secondHalf < 0)
			secondHalf *= -1;

		while((secondHalfSize < 6)){
			secondHalf *= 10;
			secondHalfSize++;
			if((int)secondHalf == 0)
				addedZeros++;
			if(secondHalfSize == 6){
				if((int)(secondHalf * 10) % 10 >= 5)
					secondHalf++;
			}
		}
		
		intToString(firstHalf);
		firstHalfSize = strsize(tempString);
		fhPointer = tempString;
		tempString = NULL;

		intToString(secondHalf);
		shPointer = tempString;
		tempString = NULL;



		tempString = (char*)malloc(firstHalfSize + addedZeros + secondHalfSize + 2);

		for(i = i; i < firstHalfSize; i++){
			tempString[i] = fhPointer[i];
		}

		if(secondHalfSize)
			tempString[i++] = '.';

		for(i = i; i < firstHalfSize + addedZeros + 1; i++){
			tempString[i] = '0';
		}

		for(i = i; i < firstHalfSize + addedZeros + secondHalfSize + 1; i++){
			tempString[i] = shPointer[i - firstHalfSize - addedZeros - 1];
		}

		free(fhPointer);
		free(shPointer);

		return tempString;

	}

	//Convert ascii integer string to an actual integer.
	long  stringToInt(char* integer, int size = 0){

		int signMultiplier = 1;
		long multiplier = 1;
		long total = 0;
		int i = 0;
		int tmp;

		ditto_compTools tools;

		//Get size if unknown..
		if(!size)
			size = tools.strsize(integer);

		//Set the sign for the integer.
		if(integer[i] == '-'){
			signMultiplier = -1;
			i++;
		}

		//Set the multiplier (highest multiple of 10).
		for(i = i; i < size - 1; i++)
			multiplier *= 10;

		//Reset i.
		i = 0;
		if(signMultiplier == -1)
			i = 1;

		//Loop through the string and determine the numeric value of each digit. Then, multiply the digit by the appropriate value of 10;
		for(i = i; i < size; i++){

			if(integer[i] == '\0')
				break;

			switch(integer[i]){
				case '0':
					tmp = 0;
					break;
				case '1':
					tmp = 1;
					break;
				case '2':
					tmp = 2;
					break;
				case '3':
					tmp = 3;
					break;
				case '4':
					tmp = 4;
					break;
				case '5':
					tmp = 5;
					break;
				case '6':
					tmp = 6;
					break;
				case '7':
					tmp = 7;
					break;
				case '8':
					tmp = 8;
					break;
				case '9':
					tmp = 9;
					break;
				default:
					tmp = (int)integer[i];
					break;
			};
			total += tmp * multiplier;
			multiplier /= 10;
		}

		return total * signMultiplier;
	}

	//Convert ascii double to an actual double.
	long double stringToDouble(char* doubleString, int size = 0){
		long double multiplier = .10;
		long secondHalf;
		long firstHalf;
		int secondSize;
		int firstSize;
		int j;

		ditto_compTools tools;
		
		//Get size if unknown..
		if(!size)
			size = tools.strsize(doubleString);

		//Get the whole number part of the doubleString.
		if(getStringTo(doubleString,'.')){

			//Get the size of the whole number part of the doubleString, then convert the whole number portion to an actual integer.
			firstSize = strsize(tempString);
			firstHalf = stringToInt(tempString,firstSize);

			//Based on the remaining characters in the doubleString, create the multiplier for the second whole number, which will become our decimal value.
			for(j = 0; j < size - firstSize - 1; j++)
				multiplier *= .10;
			secondHalf = stringToInt(&doubleString[firstSize + 1],size - firstSize);

			/*
			Multiply the second whole number (after the . split) by the multiplier in order to get our decimal value. Then add this value to the first whole number.
			Return, rinse, and repeat.
			*/

			if(firstHalf > 0)
				return firstHalf + (secondHalf * multiplier);
			return firstHalf - (secondHalf * multiplier);
		}
		else{

			//This is not a double, so return 0;
			return stringToInt(doubleString,size);
		}
	}

	//Full string comparisson. Returns 1 if strings match, and returns 0 if they don't match.
	int fullstrcmp(char* string1, char* string2){
		int s1 = 0;
		int s2 = 0;
		int i;

		//Get the size of string1.
		while(string1[s1] != '\0' && s1 < 10000)
			s1++;

		//Get the size of string2.
		while(string2[s2] != '\0' && s2 < 10000)
			s2++;

		if(s1 != s2)
			return 0;

		for(i = 0; i < s1; i++){
			if(string1[i] != string2[i])
				return 0;
		}

		return 1;

	}	
};