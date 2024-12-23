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

	// Helper function to process a character during the tokenization loop.
	bool isDigitFast(char c);
	bool isAlphaFast(char c);

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
    const std::unordered_map<std::string, std::pair<std::string, int>> reservedKeyWords = {
        {"and", {"AND", RESERVED_AND}},
        {"or", {"OR", RESERVED_OR}},
        {"if", {"IF", RESERVED_IF}},
        {"else", {"ELSE", RESERVED_ELSE}},
        {"class", {"CLASS", RESERVED_CLASS}},
        {"public", {"PUBLIC", RESERVED_PUBLIC}},
        {"private", {"PRIVATE", RESERVED_PRIVATE}},
        {"protected", {"PROTECTED", RESERVED_PROTECTED}},
        {"nil", {"NIL", RESERVED_NIL}},
        {"for", {"FOR", RESERVED_FOR}},
        {"while", {"WHILE", RESERVED_WHILE}},
        {"continue", {"CONTINUE", RESERVED_CONTINUE}},
        {"break", {"BREAK", RESERVED_BREAK}},
        {"print", {"PRINT", RESERVED_PRINT}},
        {"super", {"SUPER", RESERVED_SUPER}},
        {"this", {"THIS", RESERVED_THIS}},
        {"return", {"RETURN", RESERVED_RETURN}},
        {"void", {"VOID", RESERVED_VOID}},
        {"struct", {"STRUCT", RESERVED_STRUCT}},
        {"enum", {"ENUM", RESERVED_ENUM}},
        {"union", {"UNION", RESERVED_UNION}},
        {"int", {"INT", RESERVED_INT}},
        {"long", {"LONG", RESERVED_LONG}},
        {"short", {"SHORT", RESERVED_SHORT}},
        {"signed", {"SIGNED", RESERVED_SIGNED}},
        {"unsigned", {"UNSIGNED", RESERVED_UNSIGNED}},
        {"float", {"FLOAT", RESERVED_FLOAT}},
        {"double", {"DOUBLE", RESERVED_DOUBLE}},
        {"char", {"CHAR", RESERVED_CHAR}},
        {"str", {"STR", RESERVED_STR}},
        {"bool", {"BOOL", RESERVED_BOOL}},
        {"true", {"TRUE", RESERVED_TRUE}},
        {"false", {"FALSE", RESERVED_FALSE}},
        {"switch", {"SWITCH", RESERVED_SWITCH}},
        {"case", {"CASE", RESERVED_CASE}},
        {"default", {"DEFAULT", RESERVED_DEFAULT}},
        {"delete", {"DELETE", RESERVED_DELETE}},
        {"mutable", {"MUTABLE", RESERVED_MUTABLE}},
        {"const", {"CONST", RESERVED_CONST}},
        {"constexpr", {"CONSTEXPR", RESERVED_CONSTEXPR}},
        {"friend", {"FRIEND", RESERVED_FRIEND}},
        {"virtual", {"VIRTUAL", RESERVED_VIRTUAL}},
        {"final", {"FINAL", RESERVED_FINAL}},
        {"override", {"OVERRIDE", RESERVED_OVERRIDE}},
        {"new", {"NEW", RESERVED_NEW}},
        {"namespace", {"NAMESPACE", RESERVED_NAMESPACE}},
        {"typeof", {"TYPEOF", RESERVED_TYPEOF}},
        {"assert", {"ASSERT", RESERVED_ASSERT}},
        {"template", {"TEMPLATE", RESERVED_TEMPLATE}},
        {"typename", {"TYPENAME", RESERVED_TYPENAME}},
        {"register", {"REGISTER", RESERVED_REGISTER}},
        {"volatile", {"VOLATILE", RESERVED_VOLATILE}},
        {"static", {"STATIC", RESERVED_STATIC}},
        {"inline", {"INLINE", RESERVED_INLINE}},
        {"alignas", {"ALIGNAS", RESERVED_ALIGNAS}},
        {"alignof", {"ALIGNOF", RESERVED_ALIGNOF}},
        {"noexcept", {"NOEXCEPT", RESERVED_NOEXCEPT}},
        {"decltype", {"DECLTYPE", RESERVED_DECLTYPE}},
        {"nullptr", {"NULLPTR", RESERVED_NULLPTR}},
        {"thread_local", {"THREAD_LOCAL", RESERVED_THREAD_LOCAL}},
        {"static_cast", {"STATIC_CAST", RESERVED_STATIC_CAST}},
        {"dynamic_cast", {"DYNAMIC_CAST", RESERVED_DYNAMIC_CAST}},
        {"reinterpret_cast", {"REINTERPRET_CAST", RESERVED_REINTERPRET_CAST}},
        {"const_cast", {"CONST_CAST", RESERVED_CONST_CAST}},
        {"try", {"TRY", RESERVED_TRY}},
        {"catch", {"CATCH", RESERVED_CATCH}},
        {"explicit", {"EXPLICIT", RESERVED_EXPLICIT}},
        {"export", {"EXPORT", RESERVED_EXPORT}},
        {"import", {"IMPORT", RESERVED_IMPORT}},
        {"module", {"MODULE", RESERVED_MODULE}},
        {"requires", {"REQUIRES", RESERVED_REQUIRES}},
        {"with", {"WITH", RESERVED_WITH}},
        {"from", {"FROM", RESERVED_FROM}}
    }; // Map of reserved words and their types
};
