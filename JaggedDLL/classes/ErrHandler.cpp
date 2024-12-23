#include "ErrHandler.h"

// Constructor for the ErrHandler class
ErrHandler::ErrHandler() {
}

// Destructor for the ErrHandler class
ErrHandler::~ErrHandler() {
}

// Prints help information for the program
void ErrHandler::printHelp() {
	std::cout << "Usage: ./Jagged.exe <command> <filename> <[optional] flags>" << std::endl; // Print generic usage information for other commands
	std::cout << "\ttokenize <filename>" << std::endl; // Print usage information for tokenizing a file
	std::cout << "\tparse <filename>" << std::endl; // Print usage information for parsing a file
	// std::cout << "\tbuild <filename>" << std::endl; // Print usage information for compiling a file
	// std::cout << "\t\t--output <filename>" << std::endl; // Print usage information for specifying an output file
	// std::cout << "\t\t-o <filename>" << std::endl; // Print usage information for specifying an output file
	std::cout << "\t--version, -v" << std::endl; // Print usage information for displaying the version
	std::cout << "\t--help, -h" << std::endl; // Print usage information for displaying help
}

void ErrHandler::printVersion() {
	std::cout << "JaggedLang VERSION: v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl; // Print the version information
}

// Prints an error message to the standard error output
// @param message: The error message to be printed
void ErrHandler::printErr(std::string message, bool doExit) {
    std::cerr << RED_TEXT << message << RESET_TEXT << std::endl; // Output the error message in red
	if (doExit) {
		std::exit(ERROR_OCCURED); // Exit the program with an error code of 1
	}
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
void ErrHandler::printErr(int errCode, bool doExit) {
    switch (errCode) {
    case UNIMPLIMENTED:
        std::cerr << BOLD_RED_TEXT << "Error: Unimplemented feature." << RESET_TEXT << std::endl; // Specific error message for unimplemented feature
        std::exit(UNIMPLIMENTED); // Exit with the unimplemented feature error code
        break;
    case FILE_NOT_FOUND:
        std::cerr << BOLD_RED_TEXT << "Error: Error reading file." << RESET_TEXT << std::endl; // Specific error message for file not found
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case ERROR_OCCURED_IN_TOKENIZATION:
		std::cerr << BOLD_RED_TEXT << "Error occurred during tokenization." << RESET_TEXT << std::endl; // Specific error message for tokenization error
		std::exit(ERROR_OCCURED_IN_TOKENIZATION); // Exit with the tokenization error code
		break;
    case INVALID_ARGS:
        std::cerr << BOLD_RED_TEXT << "Error: Invalid arguments." << RESET_TEXT << std::endl; // Specific error message for invalid argument with additional info
        std::exit(INVALID_ARGS); // Exit with the invalid argument error code
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
	if (doExit) {
		std::exit(errCode); // Exit with the error code provided
	}
}

// Prints an error message based on the error code and line number provided
// @param errCode: The error code representing the type of error
// @param line_num: The line number where the error occurred
void ErrHandler::printErr(int errCode, int line_num, bool doExit) {
    switch (errCode) {
    case UNIMPLIMENTED:
        std::cerr << BOLD_RED_TEXT << "Error: Unimplemented feature." << RESET_TEXT << std::endl; // Specific error message for unimplemented feature
        std::exit(UNIMPLIMENTED); // Exit with the unimplemented feature error code
        break;
    case FILE_NOT_FOUND:
        std::cerr << BOLD_RED_TEXT << "Error: Error reading file." << RESET_TEXT << std::endl; // Specific error message for file not found
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARGS:
        std::cerr << BOLD_RED_TEXT << "Error: Invalid arguments." << RESET_TEXT << std::endl; // Specific error message for invalid argument with additional info
        std::exit(INVALID_ARGS); // Exit with the invalid argument error code
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
	if (doExit) {
		std::exit(errCode); // Exit with the error code provided
	}
}

// Prints an error message based on the error code and additional information provided
// @param errCode: The error code representing the type of error
// @param additional_info: Additional information to provide context for the error
void ErrHandler::printErr(int errCode, std::string additional_info, bool doExit) {
    switch (errCode) {
    case UNIMPLIMENTED:
        std::cerr << BOLD_RED_TEXT << "Error: Unimplemented feature: " << additional_info << RESET_TEXT << std::endl; // Specific error message for unimplemented feature
        std::exit(UNIMPLIMENTED); // Exit with the unimplemented feature error code
        break;
    case FILE_NOT_FOUND:
        std::cerr << BOLD_RED_TEXT << "Error: Error reading file: " << additional_info << RESET_TEXT << std::endl; // Specific error message for file not found with additional info
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARGS:
        std::cerr << BOLD_RED_TEXT << "Error: Invalid arguments: " << additional_info << RESET_TEXT << std::endl; // Specific error message for invalid argument with additional info
        std::exit(INVALID_ARGS); // Exit with the invalid argument error code
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
	if (doExit) {
		std::exit(errCode); // Exit with the error code provided
	}
}

// Prints an error message based on the error code, line number, and additional information provided
// @param errCode: The error code representing the type of error
// @param line_num: The line number where the error occurred
// @param additional_info: Additional information to provide context for the error
void ErrHandler::printErr(int errCode, int line_num, std::string additional_info, bool doExit) {
    switch (errCode) {
    case UNIMPLIMENTED:
        std::cerr << BOLD_RED_TEXT << "Error: Unimplemented feature: " << additional_info << RESET_TEXT << std::endl; // Specific error message for unimplemented feature
        std::exit(UNIMPLIMENTED); // Exit with the unimplemented feature error code
        break;
    case FILE_NOT_FOUND:
        std::cerr << BOLD_RED_TEXT << "Error: Error reading file: " << additional_info << RESET_TEXT << std::endl; // Specific error message for file not found with additional info
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARGS:
        std::cerr << BOLD_RED_TEXT << "Error: Invalid arguments: " << additional_info << RESET_TEXT << std::endl; // Specific error message for invalid argument with additional info
        std::exit(INVALID_ARGS); // Exit with the invalid argument error code
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
    if (doExit) {
        std::exit(errCode); // Exit with the error code provided
    }
}