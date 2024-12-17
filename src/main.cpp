#include <fstream> // Include the fstream library for file handling

#include "GLOBALS.h" // Include global definitions and constants
#include "classes/ErrHandler.h" // Include the error handling class
#include "classes/tokenizer.h" // Include the tokenizer class

// Function to read the contents of a file and return it as a string
std::string read_file_contents(const std::string& filename, ErrHandler& err);

int main(int argc, char* argv[]) {
    // Disable output buffering for immediate output to console
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Check if the correct number of command line arguments are provided
    if (argc < 3) {
        std::cerr << "Usage: ./makeKode.exe tokenize <filename>" << std::endl;
        std::cerr << "Usage: ./makeKode.exe parse <filename>" << std::endl;
        return 1; // Exit with error code 1 if usage is incorrect
    }

    const std::string command = argv[1]; // Get the command (tokenize or parse)
    ErrHandler err; // Create an instance of the error handler

    // Read the contents of the specified file
    std::string file_contents = read_file_contents(argv[2], err);
    std::vector<std::pair<std::string, int>> tokens; // Vector to store tokens and their line numbers

    // Check if the command is to tokenize the file
    if (command == "tokenize") {
        CodeTokenizer tokenizer(true); // Create a tokenizer instance with debug mode enabled

        // If the file contents are not empty, tokenize the contents
        if (!file_contents.empty()) {
            tokenizer.tokenize(file_contents, tokens, err); // Tokenize the file contents

            // Output the tokens
            std::cout << "-------------------------------------tokens-------------------------------------" << std::endl;
            for (unsigned int i = 0; i < tokens.size(); i++) {
                std::cout << tokens[i].first << std::endl; // Print each token
            }

            // Attempt to recreate the original code from tokens
            std::cout << "------------------------------attempted_recreation------------------------------" << std::endl;

            int num_lines = tokens[tokens.size() - 1].second; // Get the number of lines from the last token
            size_t num_lines_str_len = std::to_string(num_lines).size(); // Length of the number of lines
            size_t line_num_str_len; // Variable to hold the length of the current line number string

            // Loop through tokens to recreate the original code
            for (unsigned int i = 0; i < tokens.size(); i++) {
                if (tokens[i].first == "\n") { // Check for newline tokens
                    line_num_str_len = std::to_string(tokens[i].second).size(); // Get the length of the line number
                    if (i == 0) {
                        std::cout << "[" << tokens[i].second << "]"; // Print line number for the first line
                    } else if (i == tokens.size() - 1) {
                        continue; // Skip the last token if it's a newline
                    } else {
                        std::cout << "\n[" << tokens[i].second << "]"; // Print line number for subsequent lines
                    }
                    // Print spaces to align the line numbers
                    for (int i = 0; i <= num_lines_str_len - line_num_str_len; i++) {
                        std::cout << " ";
                    }
                } else {
                    std::cout << tokens[i].first; // Print the token if it's not a newline
                }
            }

            // Check if any errors occurred during tokenization
            if (tokenizer.err_present) {
                return ERROR_OCCURED_IN_TOKENIZATION; // Return error code if errors are present
            }
        } else {
            std::cout << "EOF  null" << std::endl; // Indicate end of file if contents are empty
        }
    } else if (command == "parse") {
        // -------------------- TODO: implement code parsing -------------------- //
        CodeTokenizer tokenizer; // Create a tokenizer instance for parsing

        // If the file contents are not empty, tokenize the contents
        if (!file_contents.empty()) {
            tokenizer.tokenize(file_contents, tokens, err); // Tokenize the file contents

            // Check if any errors occurred during tokenization
            if (tokenizer.err_present) {
                return ERROR_OCCURED_IN_TOKENIZATION; // Return error code if errors are present
            }
        } else {
            // Handle empty file contents for parsing (currently does nothing)
        }
    } else {
        // If the command is invalid, print an error and return an error code
        err.printErr(INVALID_ARG, command);
        return INVALID_ARG; // Return error code for invalid argument
    }

    return 0; // Return 0 to indicate successful execution
}

// Function to read the contents of a file and return it as a string
std::string read_file_contents(const std::string& filename, ErrHandler& err) {
    std::ifstream file(filename); // Open the file
    if (!file.is_open()) { // Check if the file was successfully opened
        err.printErr(FILE_NOT_FOUND, filename); // Print error if file not found
    }

    std::stringstream buffer; // Create a stringstream to hold the file contents
    buffer << file.rdbuf(); // Read the file contents into the buffer
    file.close(); // Close the file

    return buffer.str(); // Return the contents of the file as a string
}