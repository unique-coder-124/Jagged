#pragma once

#include "../GLOBALS.h"

// Define DLL export/import based on the compilation
#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

// ANSI escape codes for red and bold red text
#define RED_TEXT "\033[31m"
#define BOLD_RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

// Class definition for ErrHandler, which is responsible for handling and printing error messages
class DLL_EXPORT ErrHandler : public std::exception {
public:
    // Constructor for ErrHandler
    ErrHandler();

    // Destructor for ErrHandler
    ~ErrHandler();

    // Prints help information for the program
    void printHelp();

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
