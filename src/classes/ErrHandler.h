#pragma once // Ensures that this header file is included only once in a single compilation

#include "../GLOBALS.h" // Includes the GLOBALS.h header file, which likely contains global definitions or constants

// Class definition for ErrHandler, which is responsible for handling and printing error messages
class ErrHandler {
public:
	// Constructor for ErrHandler
	ErrHandler();

	// Destructor for ErrHandler
	~ErrHandler();

	// Prints an error message to the console
	void printErr(std::string message);

	// Prints an error message and exits the program with a specified exit code
	void printErr(std::string message, int exit_code);

	// Prints an error based on an error code
	void printErr(int errCode);

	// Prints an error based on an error code and the line number where the error occurred
	void printErr(int errCode, int line_num);

	// Prints an error based on an error code and additional information
	void printErr(int errCode, std::string additional_info);

	// Prints an error based on an error code, line number, and additional information
	void printErr(int errCode, int line_num, std::string additional_info);

private:
	// Private members can be added here if needed in the future
};