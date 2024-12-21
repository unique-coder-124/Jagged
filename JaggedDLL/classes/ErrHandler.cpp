#include "ErrHandler.h"

// Constructor for the ErrHandler class
ErrHandler::ErrHandler() {
}

// Destructor for the ErrHandler class
ErrHandler::~ErrHandler() {
}

// Prints help information for the program
void ErrHandler::printHelp() {
	std::cout << "Usage: ./makeKode.exe <command> <filename>" << std::endl; // Print generic usage information for other commands
	std::cout << "\ttokenize <filename>" << std::endl; // Print usage information for tokenizing a file
	std::cout << "\tparse <filename>" << std::endl; // Print usage information for parsing a file
	std::cout << "\trun <filename>" << std::endl; // Print usage information for running a file
	std::cout << "\t\t--compile" << std::endl; // Print usage information for compiling a file before running
	std::cout << "\t\t\t--output <output_filename>" << std::endl; // Print usage information for specifying an output filename
	std::cout << "\t\t--run_only" << std::endl; // Print usage information for running a file without compiling
	std::cout << "\tcompile <filename>" << std::endl; // Print usage information for compiling a file
    std::cout << "\t\t--output <output_filename>" << std::endl; // Print usage information for specifying an output filename
    std::cout << "\t\t-o <output_filename>" << std::endl; // Print usage information for specifying an output filename
    std::cout << "\t\t--flags <compiler_flags>" << std::endl; // Print usage information for specifying compiler flags
	std::cout << "\t\t--debug" << std::endl; // Print usage information for enabling debug mode
	std::cout << "\t\t--compile_to_cpp" << std::endl; // Print usage information for compiling to C++ code
    std::cout << "\t\t-c2c" << std::endl; // Print usage information for compiling to C++ code
    std::cout << "\t\t--compile_to_obj" << std::endl; // Print usage information for compiling to object file
	std::cout << "\t\t-c2o" << std::endl; // Print usage information for compiling to object file
	std::cout << "\t\t--compile_to_exe" << std::endl; // Print usage information for compiling to executable file
	std::cout << "\t\t-c2e" << std::endl; // Print usage information for compiling to executable file
	std::cout << "\t\t--compile_to_dll" << std::endl; // Print usage information for compiling to dynamic link library
	std::cout << "\t\t-c2d" << std::endl; // Print usage information for compiling to dynamic link library
	std::cout << "\t\t--compile_to_static_lib" << std::endl; // Print usage information for compiling to static library
	std::cout << "\t\t-c2s" << std::endl; // Print usage information for compiling to static library
	std::cout << "\ttest <filename>" << std::endl; // Print usage information for testing a file
    std::cout << "\tversion" << std::endl; // Print usage information for displaying the program version
    std::cout << "\t-v" << std::endl; // Print usage information for displaying the program version
    std::cout << "\thelp" << std::endl; // Print usage information for displaying help information
    std::cout << "\t-h" << std::endl; // Print usage information for displaying help information
}

// Prints an error message to the standard error output
// @param message: The error message to be printed
void ErrHandler::printErr(std::string message) {
    std::cerr << RED_TEXT << message << RESET_TEXT << std::endl; // Output the error message in red
}

// Prints an error message and exits the program with a specified exit code
// @param message: The error message to be printed
// @param exit_code: The exit code to terminate the program
void ErrHandler::printErr(std::string message, int exit_code) {
    std::cerr << BOLD_RED_TEXT << message << RESET_TEXT << std::endl; // Output the error message in bold red
    std::exit(exit_code); // Exit the program with the specified exit code
}

// Prints an error message based on the error code provided
// @param errCode: The error code representing the type of error
void ErrHandler::printErr(int errCode) {
    switch (errCode) {
    case FILE_NOT_FOUND:
        std::cerr << BOLD_RED_TEXT << "Error reading file." << RESET_TEXT << std::endl; // Specific error message for file not found
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case ERROR_OCCURED_IN_TOKENIZATION:
		std::cerr << BOLD_RED_TEXT << "Error occurred during tokenization." << RESET_TEXT << std::endl; // Specific error message for tokenization error
		std::exit(ERROR_OCCURED_IN_TOKENIZATION); // Exit with the tokenization error code
		break;
    case INVALID_ARG:
        std::cerr << BOLD_RED_TEXT << "Unknown command." << RESET_TEXT << std::endl; // Specific error message for invalid argument
        std::exit(INVALID_ARG); // Exit with the invalid argument error code
        break;
    case UNTERMINATED_STR:
        std::cerr << RED_TEXT << "Error: Unterminated string." << RESET_TEXT << std::endl; // Error for unterminated string
        break;
    case UNTERMINATED_BRACE:
        std::cerr << RED_TEXT << "Error: Unterminated brace." << RESET_TEXT << std::endl; // Error for unterminated brace
        break;
    case UNTERMINATED_BRACKET:
        std::cerr << RED_TEXT << "Error: Unterminated bracket." << RESET_TEXT << std::endl; // Error for unterminated bracket
        break;
    case UNTERMINATED_PARENTHESES:
        std::cerr << RED_TEXT << "Error: Unterminated parentheses." << RESET_TEXT << std::endl; // Error for unterminated parentheses
        break;
    case UNEXPECTED_CHAR:
        std::cerr << RED_TEXT << "Error: Unexpected character." << RESET_TEXT << std::endl; // Error for unexpected character
        break;
    case MALFORMED_CHAR:
        std::cerr << RED_TEXT << "Error: Malformed character." << RESET_TEXT << std::endl; // Error for malformed character
        break;
    default:
        std::cerr << RED_TEXT << "Error: Unknown error occurred." << RESET_TEXT << std::endl; // Generic error message for unknown errors
        break;
    }
}

// Prints an error message based on the error code and line number provided
// @param errCode: The error code representing the type of error
// @param line_num: The line number where the error occurred
void ErrHandler::printErr(int errCode, int line_num) {
    switch (errCode) {
    case FILE_NOT_FOUND:
        std::cerr << BOLD_RED_TEXT << "Error reading file." << RESET_TEXT << std::endl; // Specific error message for file not found
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARG:
        std::cerr << BOLD_RED_TEXT << "Unknown command." << RESET_TEXT << std::endl; // Specific error message for invalid argument
        std::exit(INVALID_ARG); // Exit with the invalid argument error code
        break;
    case UNTERMINATED_STR:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unterminated string." << RESET_TEXT << std::endl; // Error for unterminated string with line number
        break;
    case UNTERMINATED_BRACE:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unterminated brace." << RESET_TEXT << std::endl; // Error for unterminated brace with line number
        break;
    case UNTERMINATED_BRACKET:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unterminated bracket." << RESET_TEXT << std::endl; // Error for unterminated bracket with line number
        break;
    case UNTERMINATED_PARENTHESES:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unterminated parentheses." << RESET_TEXT << std::endl; // Error for unterminated parentheses with line number
        break;
    case UNEXPECTED_CHAR:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unexpected character." << RESET_TEXT << std::endl; // Error for unexpected character with line number
        break;
    case MALFORMED_CHAR:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Malformed character." << RESET_TEXT << std::endl; // Error for malformed character with line number
        break;
    default:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unknown error occurred." << RESET_TEXT << std::endl; // Generic error message for unknown errors with line number
        break;
    }
}

// Prints an error message based on the error code and additional information provided
// @param errCode: The error code representing the type of error
// @param additional_info: Additional information to provide context for the error
void ErrHandler::printErr(int errCode, std::string additional_info) {
    switch (errCode) {
    case FILE_NOT_FOUND:
        std::cerr << BOLD_RED_TEXT << "Error reading file: " << additional_info << RESET_TEXT << std::endl; // Specific error message for file not found with additional info
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARG:
        std::cerr << BOLD_RED_TEXT << "Unknown command: " << additional_info << RESET_TEXT << std::endl; // Specific error message for invalid argument with additional info
        std::exit(INVALID_ARG); // Exit with the invalid argument error code
        break;
    case UNTERMINATED_STR:
        std::cerr << RED_TEXT << "Error: Unterminated string: " << additional_info << RESET_TEXT << std::endl; // Error for unterminated string with additional info
        break;
    case UNTERMINATED_BRACE:
        std::cerr << RED_TEXT << "Error: Unterminated brace: " << additional_info << RESET_TEXT << std::endl; // Error for unterminated brace with additional info
        break;
    case UNTERMINATED_BRACKET:
        std::cerr << RED_TEXT << "Error: Unterminated bracket: " << additional_info << RESET_TEXT << std::endl; // Error for unterminated bracket with additional info
        break;
    case UNTERMINATED_PARENTHESES:
        std::cerr << RED_TEXT << "Error: Unterminated parentheses: " << additional_info << RESET_TEXT << std::endl; // Error for unterminated parentheses with additional info
        break;
    case UNEXPECTED_CHAR:
        std::cerr << RED_TEXT << "Error: Unexpected character: " << additional_info << RESET_TEXT << std::endl; // Error for unexpected character with additional info
        break;
    case MALFORMED_CHAR:
        std::cerr << RED_TEXT << "Error: Malformed character: " << additional_info << RESET_TEXT << std::endl; // Error for malformed character with additional info
        break;
    default:
        std::cerr << RED_TEXT << "Error: Unknown error occurred: " << additional_info << RESET_TEXT << std::endl; // Generic error message for unknown errors with additional info
        break;
    }
}

// Prints an error message based on the error code, line number, and additional information provided
// @param errCode: The error code representing the type of error
// @param line_num: The line number where the error occurred
// @param additional_info: Additional information to provide context for the error
void ErrHandler::printErr(int errCode, int line_num, std::string additional_info) {
    switch (errCode) {
    case FILE_NOT_FOUND:
        std::cerr << BOLD_RED_TEXT << "Error reading file: " << additional_info << RESET_TEXT << std::endl; // Specific error message for file not found with additional info
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARG:
        std::cerr << BOLD_RED_TEXT << "Unknown command: " << additional_info << RESET_TEXT << std::endl; // Specific error message for invalid argument with additional info
        std::exit(INVALID_ARG); // Exit with the invalid argument error code
        break;
    case UNTERMINATED_STR:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unterminated string: " << additional_info << RESET_TEXT << std::endl; // Error for unterminated string with line number and additional info
        break;
    case UNTERMINATED_BRACE:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unterminated brace: " << additional_info << RESET_TEXT << std::endl; // Error for unterminated brace with line number and additional info
        break;
    case UNTERMINATED_BRACKET:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unterminated bracket: " << additional_info << RESET_TEXT << std::endl; // Error for unterminated bracket with line number and additional info
        break;
    case UNTERMINATED_PARENTHESES:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unterminated parentheses: " << additional_info << RESET_TEXT << std::endl; // Error for unterminated parentheses with line number and additional info
        break;
    case UNEXPECTED_CHAR:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unexpected character: " << additional_info << RESET_TEXT << std::endl; // Error for unexpected character with line number and additional info
        break;
    case MALFORMED_CHAR:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Malformed character: " << additional_info << RESET_TEXT << std::endl; // Error for malformed character with line number and additional info
        break;
    default:
        std::cerr << RED_TEXT << "[line " << line_num << "] Error: Unknown error occurred: " << additional_info << RESET_TEXT << std::endl; // Generic error message for unknown errors with line number and additional info
        break;
    }
}