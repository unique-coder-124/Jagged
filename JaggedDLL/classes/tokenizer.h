#pragma once

#include "../GLOBALS.h"
#include "ErrHandler.h"

// Define DLL export/import based on the compilation
#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

// Class responsible for tokenizing code from a given string input.
class DLL_EXPORT CodeTokenizer {
public:
    // Default constructor for CodeTokenizer.
    CodeTokenizer();

    // Constructor that allows enabling debug mode.
    CodeTokenizer(bool debug);

    // Destructor for CodeTokenizer.
    ~CodeTokenizer();

    // Flag to indicate if an error is present during tokenization.
    bool err_present;

    // Main function to tokenize the provided file contents.
    // Takes a reference to the file contents string, a vector to store tokens,
    // and an error handler object to manage errors.
    int tokenize(std::string& file_contents, std::vector<std::pair<std::string, int>>& tokens, ErrHandler& err);

private:
    // Helper function to process a character during the tokenization loop.
    // Takes a character and a vector to store tokens.
    int tokenizeLoop(char c, std::vector<std::pair<std::string, int>>& tokens);

    // Mode of operation for the tokenizer (e.g., different parsing modes).
    int mode;

    // Current line number being processed.
    int line_num;

    // Last token processed, used for context in tokenization.
    std::string last_tok;

    // Flag indicating if a left delimiter parenthesis is open.
    bool left_dp;

    // Vector to store error codes encountered during tokenization.
    std::vector<int> errors;

    // Status of the tokenization process.
    int tokenizeStatus;

    // Type of error encountered during tokenization.
    int err_type;

    // Additional information about the error, if any.
    std::string additionalErrorInfo;

    // Flag to indicate if debug mode is enabled.
    bool debug;

    // Variables to hold different types of values encountered during tokenization.
    int intValue;          // Integer value
    float floatValue;      // Floating-point value
    std::string strValue;  // String value
    std::string identifierName; // Name of the identifier
    std::pair<std::string, int> reservedName; // Reserved name with its type
    char terminator_char;  // Character used to terminate tokens
    const std::unordered_map<std::string, std::pair<std::string, int>> reservedKeyWords; // Map of reserved words and their types
};
