#pragma once

#include "../GLOBALS.h"
#include "ErrHandler.h"

// Define DLL export/import based on the compilation
#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

class DLL_EXPORT CodeParser {
public:
	// Default constructor for CodeParser.
	CodeParser();

	// Constructor that allows enabling debug mode.
	CodeParser(bool debug);

	// Destructor for CodeParser.
	~CodeParser();

	// Flag to indicate if an error is present during parsing.
	bool err_present;

	// Main function to parse the provided tokens.
	int parse(JaggedTypes::TokenArr& tokens, JaggedTypes::Context ContextHead, ErrHandler& err); // Vector to store parsed tokens and their types in the main tokens vector
private:

	// Helper function to process a token during the parsing loop.
	int parseLoop(int token_idx, JaggedTypes::TokenArr& tokens, JaggedTypes::Context ContextNode);

	// Helper function to handle reserved keywords and operators.
	int handleReserved(JaggedTypes::Token token);

	// Fast check for digit characters
	bool isDigitFast(char c);

	// Fast check for alphabetic characters
	bool isAlphaFast(char c);

	// Current line number being processed.
	int line_num;

	// Last token processed, used for context in parsing.
	JaggedTypes::Token last_tok;

	// output stack
	JaggedTypes::Expression output;

	// holding stack
	std::stack<JaggedTypes::Token> holding;
	
	// operator precedence
	std::unordered_map<std::string, int> precedence = {
	};

	// Mode of operation for the parser (e.g., different parsing modes).
	int mode;

	// Status of the parsing process.
	int parseStatus;

	// Additional information about the error, if any.
	std::string additionalErrorInfo;

	// Type of error encountered during parsing.
	int err_type;

	// Flag to indicate if debug mode is enabled.
	bool debug;
};