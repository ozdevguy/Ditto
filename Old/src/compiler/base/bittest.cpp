#include <iostream>
typedef unsigned char byte;

int main(int argc, char* argv[]){
	int x =  -2147483640;

	byte y1 = x;
	byte y2 = (x >> 8);
	byte y3 = (x >> 16);
	byte y4 = (x >> 24);

	int alpha;

	alpha = 0;
	alpha += (y4 << 24);
	alpha += (y3 << 16);
	alpha += (y2 << 8);
	alpha += y1;

	std::cout << "\nThe Value: " << alpha << "\n";

	unsigned char test = 81;
	unsigned int test2 = (test << 4);
	test2 = (test2 >> 4);
	std::cout << test2 << "\n";

	return 0;
}