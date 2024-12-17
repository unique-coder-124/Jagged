#include "ErrHandler.h"

// Constructor for the ErrHandler class
ErrHandler::ErrHandler() {
}

// Destructor for the ErrHandler class
ErrHandler::~ErrHandler() {
}

// Prints an error message to the standard error output
// @param message: The error message to be printed
void ErrHandler::printErr(std::string message) {
    std::cerr << message << std::endl; // Output the error message
}

// Prints an error message and exits the program with a specified exit code
// @param message: The error message to be printed
// @param exit_code: The exit code to terminate the program
void ErrHandler::printErr(std::string message, int exit_code) {
    ErrHandler::printErr(message); // Call the single message print function
    std::exit(exit_code); // Exit the program with the specified exit code
}

// Prints an error message based on the error code provided
// @param errCode: The error code representing the type of error
void ErrHandler::printErr(int errCode) {
    switch (errCode) {
    case FILE_NOT_FOUND:
        std::cerr << "Error reading file." << std::endl; // Specific error message for file not found
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARG:
        std::cerr << "Unknown command." << std::endl; // Specific error message for invalid argument
        std::exit(INVALID_ARG); // Exit with the invalid argument error code
        break;
    case UNTERMINATED_STR:
        std::cerr << "Error: Unterminated string." << std::endl; // Error for unterminated string
        break;
    case UNTERMINATED_BRACE:
        std::cerr << "Error: Unterminated brace." << std::endl; // Error for unterminated brace
        break;
    case UNTERMINATED_BRACKET:
        std::cerr << "Error: Unterminated bracket." << std::endl; // Error for unterminated bracket
        break;
    case UNTERMINATED_PARENTHESES:
        std::cerr << "Error: Unterminated parentheses." << std::endl; // Error for unterminated parentheses
        break;
    case UNEXPECTED_CHAR:
        std::cerr << "Error: Unexpected character." << std::endl; // Error for unexpected character
        break;
    default:
        std::cerr << "Error: Unknown error occurred." << std::endl; // Generic error message for unknown errors
        break;
    }
}

// Prints an error message based on the error code and line number provided
// @param errCode: The error code representing the type of error
// @param line_num: The line number where the error occurred
void ErrHandler::printErr(int errCode, int line_num) {
    switch (errCode) {
    case FILE_NOT_FOUND:
        std::cerr << "Error reading file." << std::endl; // Specific error message for file not found
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARG:
        std::cerr << "Unknown command." << std::endl; // Specific error message for invalid argument
        std::exit(INVALID_ARG); // Exit with the invalid argument error code
        break;
    case UNTERMINATED_STR:
        std::cerr << "[line " << line_num << "] Error: Unterminated string." << std::endl; // Error for unterminated string with line number
        break;
    case UNTERMINATED_BRACE:
        std::cerr << "[line " << line_num << "] Error: Unterminated brace." << std::endl; // Error for unterminated brace with line number
        break;
    case UNTERMINATED_BRACKET:
        std::cerr << "[line " << line_num << "] Error: Unterminated bracket." << std::endl; // Error for unterminated bracket with line number
        break;
    case UNTERMINATED_PARENTHESES:
        std::cerr << "[line " << line_num << "] Error: Unterminated parentheses." << std::endl; // Error for unterminated parentheses with line number
        break;
    case UNEXPECTED_CHAR:
        std::cerr << "[line " << line_num << "] Error: Unexpected character." << std::endl; // Error for unexpected character with line number
        break;
    default:
        std::cerr << "[line " << line_num << "] Error: Unknown error occurred." << std::endl; // Generic error message for unknown errors with line number
        break;
    }
}

// Prints an error message based on the error code and additional information provided
// @param errCode: The error code representing the type of error
// @param additional_info: Additional information to provide context for the error
void ErrHandler::printErr(int errCode, std::string additional_info) {
    switch (errCode) {
    case FILE_NOT_FOUND:
        std::cerr << "Error reading file: " << additional_info << std::endl; // Specific error message for file not found with additional info
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARG:
        std::cerr << "Unknown command: " << additional_info << std::endl; // Specific error message for invalid argument with additional info
        std::exit(INVALID_ARG); // Exit with the invalid argument error code
        break;
    case UNTERMINATED_STR:
        std::cerr << "Error: Unterminated string: " << additional_info << std::endl; // Error for unterminated string with additional info
        break;
    case UNTERMINATED_BRACE:
        std::cerr << "Error: Unterminated brace: " << additional_info << std::endl; // Error for unterminated brace with additional info
        break;
    case UNTERMINATED_BRACKET:
        std::cerr << "Error: Unterminated bracket: " << additional_info << std::endl; // Error for unterminated bracket with additional info
        break;
    case UNTERMINATED_PARENTHESES:
        std::cerr << "Error: Unterminated parentheses: " << additional_info << std::endl; // Error for unterminated parentheses with additional info
        break;
    case UNEXPECTED_CHAR:
        std::cerr << "Error: Unexpected character: " << additional_info << std::endl; // Error for unexpected character with additional info
        break;
    default:
        std::cerr << "Error: Unknown error occurred: " << additional_info << std::endl; // Generic error message for unknown errors with additional info
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
        std::cerr << "Error reading file: " << additional_info << std::endl; // Specific error message for file not found with additional info
        std::exit(FILE_NOT_FOUND); // Exit with the file not found error code
        break;
    case INVALID_ARG:
        std::cerr << "Unknown command: " << additional_info << std::endl; // Specific error message for invalid argument with additional info
        std::exit(INVALID_ARG); // Exit with the invalid argument error code
        break;
    case UNTERMINATED_STR:
        std::cerr << "[line " << line_num << "] Error: Unterminated string: " << additional_info << std::endl; // Error for unterminated string with line number and additional info
        break;
    case UNTERMINATED_BRACE:
        std::cerr << "[line " << line_num << "] Error: Unterminated brace: " << additional_info << std::endl; // Error for unterminated brace with line number and additional info
        break;
    case UNTERMINATED_BRACKET:
        std::cerr << "[line " << line_num << "] Error: Unterminated bracket: " << additional_info << std::endl; // Error for unterminated bracket with line number and additional info
        break;
    case UNTERMINATED_PARENTHESES:
        std::cerr << "[line " << line_num << "] Error: Unterminated parentheses: " << additional_info << std::endl; // Error for unterminated parentheses with line number and additional info
        break;
    case UNEXPECTED_CHAR:
        std::cerr << "[line " << line_num << "] Error: Unexpected character: " << additional_info << std::endl; // Error for unexpected character with line number and additional info
        break;
    default:
        std::cerr << "[line " << line_num << "] Error: Unknown error occurred: " << additional_info << std::endl; // Generic error message for unknown errors with line number and additional info
        break;
    }
}