#include <fstream> // Include the fstream library for file handling
#include <functional> // Include the function library for function objects

#include "GLOBALS.h" // Include global definitions and constants
#include "classes/ErrHandler.h" // Include the error handling class
#include "classes/tokenizer.h" // Include the tokenizer class

// Function to read the contents of a file and return it as a string
std::string read_file_contents(const std::string& filename, ErrHandler& err);

void version(ErrHandler err);
void help(ErrHandler err);
int tokenize(const std::string& fileName, ErrHandler err);
int parse(const std::string& fileName, ErrHandler err);
// int run(const std::string& fileName, ErrHandler err);
// int build(const std::string& fileName, ErrHandler err);
// int output(const std::string& fileName, ErrHandler err);

int main(int argc, char* argv[]) {
    // Disable output buffering for immediate output to console
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    ErrHandler err; // Create an instance of the error handler

    // Check if the correct number of command line arguments are provided
    if (argc < 2) {
		err.printHelp(); // Print help information if usage is incorrect
        return NONE; // Exit with error code 1 if usage is incorrect
    }

    const std::string command = argv[1]; // Get the command (tokenize or parse)

	std::function<int()> commandToExecute; // Function object to store the command to execute

	std::string currentCommand; // Get the command (tokenize or parse)
	std::string argFlagCommand; // Get the argument flag command
	std::string strArg; // Get the file name

	std::unordered_map<std::string, std::function<int(const std::string, ErrHandler)>> FuncMap = {
		{ "tokenize", tokenize },
		{ "parse", parse }
        // { "run", run }
		// { "build", build }
    }; // Map to store function pointers

	std::unordered_map<std::string, std::function<void(ErrHandler)>> terminatorFlags = {
        { "--version", version },
		{ "-v", version },
		{ "--help", help },
		{ "-h" , help }
	}; // Map to store functions that don't need arguments

	std::unordered_map<std::string, std::function<void(ErrHandler)>> noArgFlags = {}; // Map to store functions that don't need arguments

	std::unordered_map<std::string, std::function<int(const std::string, ErrHandler)>> argFlags = {
        // { "--output", output }
    }; // Map to store functions that need arguments

    if (FuncMap.find(argv[1]) != FuncMap.end()) {
        if ((currentCommand != "") || (argc < 3)) {
            err.printErr(INVALID_ARGS, argv[1]);
			if (argc < 3) {
				err.printHelp();
				return NONE;
			}
        } else {
            currentCommand = argv[1];
        }
    } else if (terminatorFlags.find(argv[1]) != terminatorFlags.end()) {
        terminatorFlags[argv[1]](err);
        return NONE;
	} else {
		err.printErr(INVALID_ARGS, argv[1]);
	}

	// Print the command line arguments
	for (int i = 2; i < argc; i++) {
		std::cout << "argv[" << i << "]: " << argv[i] << std::endl; // Print each command line argument
        if (noArgFlags.find(argv[i]) != noArgFlags.end()) {
            noArgFlags[argv[i]](err);
		} else if (argFlags.find(argv[i]) != argFlags.end()) {
			if (argFlagCommand != "") {
				err.printErr(INVALID_ARGS, argv[i]);
			} else {
				argFlagCommand = argv[i];
			}
		} else {
            if ((currentCommand == "") && (argFlagCommand == "")) {
				err.printErr(INVALID_ARGS, argv[i]);
            } else {
                strArg = argv[i];
				if (currentCommand != "") {
                    commandToExecute = std::bind(FuncMap[currentCommand], strArg, err);
					currentCommand = "";
				} else if (argFlagCommand != "") {
					argFlags[argFlagCommand](strArg, err);
					argFlagCommand = "";
				}
            }
        }
    }

	commandToExecute(); // Execute the command

    // Read the contents of the specified file
    std::string file_contents = read_file_contents(argv[2], err);

	// Declare tokens vector
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
            std::cout << "EOF  null" << std::endl; // Indicate end of file if contents are empty
        }
    } else {
        // If the command is invalid, print an error and return an error code
        err.printErr(INVALID_ARGS, command);
        return INVALID_ARGS; // Return error code for invalid argument
    }
    return NONE; // Return NONE to indicate successful execution
}

void version(ErrHandler err) {
	err.printVersion(); // Print version information
}

void help(ErrHandler err) {
	err.printHelp(); // Print help information
}

int tokenize(const std::string& fileName, ErrHandler err) {
	std::cout << "Tokenizing input: " << fileName << std::endl; // Print the input to be tokenized
    return UNIMPLIMENTED;
}

int parse(const std::string& fileName, ErrHandler err) {
	std::cout << "Parsing input: " << fileName << std::endl; // Print the input to be parsed
    return UNIMPLIMENTED;
}

// int run(const std::string& fileName, ErrHandler err) {
// 	std::cout << "Running input: " << fileName << std::endl; // Print the input to be run
// }

// int build(const std::string& fileName, ErrHandler err) {
// 	std::cout << "Building input: " << fileName << std::endl; // Print the input to be built
// }

// int output(const std::string& fileName, ErrHandler err) {
// 	std::cout << "Outputting to: " << fileName << std::endl; // Print the output file name
// }

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
