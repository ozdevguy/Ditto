/*
This file contains the error parser, which specifies different types of compiler errors.
*/

namespace __ditto_compiler{
	class errorHandler{
	private:
		char* errors;

	public:
		void integerArrayOverflow(){
			std::cout << "\nERROR: The specified offset is greater than the total size of the given array!\n";
		}
	};
};