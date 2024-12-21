#include <fstream> // Include the fstream library for file handling
#include <functional> // Include the functional library for std::function

#include "GLOBALS.h" // Include global definitions and constants
#include "classes/ErrHandler.h" // Include the error handling class
#include "classes/tokenizer.h" // Include the tokenizer class

// Function to read the contents of a file and return it as a string
std::string read_file_contents(const std::string& filename, ErrHandler& err);

// Function to handle the "tokenize" command
int handle_tokenize(const std::string& filename, ErrHandler& err) {
    std::string file_contents = read_file_contents(filename, err);
    std::vector<std::pair<std::string, int>> tokens;

    CodeTokenizer tokenizer(true); // Create a tokenizer instance with debug mode enabled

    if (!file_contents.empty()) {
        tokenizer.tokenize(file_contents, tokens, err);

        std::cout << "-----------------------------------raw-tokens-----------------------------------" << std::endl;
        for (const auto& token : tokens) {
            std::cout << token.first << std::endl;
        }

        std::cout << "------------------------------attempted-recreation------------------------------" << std::endl;

        int num_lines = tokens.back().second;
        size_t num_lines_str_len = std::to_string(num_lines).size();

        for (const auto& token : tokens) {
            if (token.first == "\n") {
                size_t line_num_str_len = std::to_string(token.second).size();
                std::cout << "\n" << token.second << ":";
                for (size_t i = 0; i <= num_lines_str_len - line_num_str_len; i++) {
                    std::cout << " ";
                }
            } else {
                std::cout << token.first;
            }
        }

        std::cout << std::endl;

        if (tokenizer.err_present) {
			err.printErr(ERROR_OCCURED_IN_TOKENIZATION);
            return ERROR_OCCURED_IN_TOKENIZATION;
        }
    } else {
        std::cout << "EOF  null" << std::endl;
    }

    return 0;
}

// Function to handle the "parse" command
int handle_parse(const std::string& filename, ErrHandler& err) {
    std::string file_contents = read_file_contents(filename, err);
    std::vector<std::pair<std::string, int>> tokens;

    CodeTokenizer tokenizer;

    if (!file_contents.empty()) {
        tokenizer.tokenize(file_contents, tokens, err);

        if (tokenizer.err_present) {
            return ERROR_OCCURED_IN_TOKENIZATION;
        }
    }

    // TODO: Implement parsing logic here

    return 0;
}

// Function to handle the "help" command
int handle_help(ErrHandler& err) {
    err.printHelp();
    return 0;
}

// Function to handle the "run" command
int handle_run(const std::string& filename, ErrHandler& err, bool compile, const std::string& output_filename) {
    if (compile) {
        // TODO: Implement compile logic here
        if (!output_filename.empty()) {
            // TODO: Implement logic to specify output filename
        }
    }
    // TODO: Implement run logic here
    return 0;
}

// Function to handle the "compile" command
int handle_compile(const std::string& filename, ErrHandler& err, const std::string& output_filename, const std::string& flags) {
    // TODO: Implement compile logic here
    if (!output_filename.empty()) {
        // TODO: Implement logic to specify output filename
    }
    if (!flags.empty()) {
        // TODO: Implement logic to specify compiler flags
    }
    return 0;
}

// Function to handle the "test" command
int handle_test(const std::string& filename, ErrHandler& err) {
    // TODO: Implement test logic here
    return 0;
}

// Function to handle the "version" command
int handle_version(ErrHandler& err) {
    std::cout << "Version " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    ErrHandler err;

    if (argc < 2) {
        err.printHelp();
        return 1;
    }

    const std::string command = argv[1];
    const std::string filename = (argc > 2) ? argv[2] : "";
    std::string output_filename;
    std::string flags;
    bool compile = false;
    bool run_only = false;

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--compile") {
            compile = true;
        } else if (arg == "--run_only") {
            run_only = true;
        } else if (arg == "--output" || arg == "-o") {
            if (i + 1 < argc) {
                output_filename = argv[++i];
            } else {
                err.printErr("Output filename not specified", INVALID_ARG);
                return INVALID_ARG;
            }
        } else if (arg == "--flags") {
            if (i + 1 < argc) {
                flags = argv[++i];
            } else {
                err.printErr("Compiler flags not specified", INVALID_ARG);
                return INVALID_ARG;
            }
        } else {
            err.printErr("Unknown argument: " + arg, INVALID_ARG);
            return INVALID_ARG;
        }
    }

    std::unordered_map<std::string, std::function<int(const std::string&, ErrHandler&)>> command_map = {
        {"tokenize", handle_tokenize},
        {"parse", handle_parse},
        {"help", [](const std::string&, ErrHandler& err) { return handle_help(err); }},
        {"-h", [](const std::string&, ErrHandler& err) { return handle_help(err); }},
        {"run", [&](const std::string& filename, ErrHandler& err) { return handle_run(filename, err, compile, output_filename); }},
        {"compile", [&](const std::string& filename, ErrHandler& err) { return handle_compile(filename, err, output_filename, flags); }},
        {"test", handle_test},
        {"version", [](const std::string&, ErrHandler& err) { return handle_version(err); }},
        {"-v", [](const std::string&, ErrHandler& err) { return handle_version(err); }},
    };

    auto it = command_map.find(command);
    if (it != command_map.end()) {
        return it->second(filename, err);
    } else {
        err.printErr("Invalid argument: " + command, INVALID_ARG);
        return INVALID_ARG;
    }

    return 0;
}

// Function to read the contents of a file and return it as a string
std::string read_file_contents(const std::string& filename, ErrHandler& err) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        err.printErr(FILE_NOT_FOUND, filename);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}