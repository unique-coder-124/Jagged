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
    int tokenize(std::string& file_contents, JaggedTypes::TokenArr& tokens, ErrHandler& err);
private:
    // Helper function to process a character during the tokenization loop.
    // Takes a character and a vector to store tokens.
    int tokenizeLoop(char c, JaggedTypes::TokenArr& tokens);

    // Fast check for digit characters
    bool isDigitFast(char c);

    // Fast check for alphabetic characters
    bool isAlphaFast(char c);

    // Mode of operation for the tokenizer (e.g., different parsing modes).
    int mode;

    // Current line number being processed.
    int line_num;

    // Last token processed, used for context in tokenization.
    std::string last_tok;

    // Flag indicating if digit is left of decimal point.
    bool left_dp;

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
        {"alignas", {"ALIGNAS", RESERVED_ALIGNAS}},
        {"alignof", {"ALIGNOF", RESERVED_ALIGNOF}},
        {"and", {"AND", RESERVED_AND}},
        {"assert", {"ASSERT", RESERVED_ASSERT}},
        {"bool", {"BOOL", RESERVED_BOOL}},
        {"break", {"BREAK", RESERVED_BREAK}},
        {"case", {"CASE", RESERVED_CASE}},
        {"catch", {"CATCH", RESERVED_CATCH}},
        {"char", {"CHAR", RESERVED_CHAR}},
        {"class", {"CLASS", RESERVED_CLASS}},
        {"const", {"CONST", RESERVED_CONST}},
        {"const_cast", {"CONST_CAST", RESERVED_CONST_CAST}},
        {"constexpr", {"CONSTEXPR", RESERVED_CONSTEXPR}},
        {"continue", {"CONTINUE", RESERVED_CONTINUE}},
        {"decltype", {"DECLTYPE", RESERVED_DECLTYPE}},
        {"default", {"DEFAULT", RESERVED_DEFAULT}},
        {"delete", {"DELETE", RESERVED_DELETE}},
        {"double", {"DOUBLE", RESERVED_DOUBLE}},
        {"dynamic_cast", {"DYNAMIC_CAST", RESERVED_DYNAMIC_CAST}},
        {"else", {"ELSE", RESERVED_ELSE}},
        {"enum", {"ENUM", RESERVED_ENUM}},
        {"explicit", {"EXPLICIT", RESERVED_EXPLICIT}},
        {"export", {"EXPORT", RESERVED_EXPORT}},
        {"false", {"FALSE", RESERVED_FALSE}},
        {"final", {"FINAL", RESERVED_FINAL}},
        {"float", {"FLOAT", RESERVED_FLOAT}},
        {"for", {"FOR", RESERVED_FOR}},
        {"friend", {"FRIEND", RESERVED_FRIEND}},
        {"from", {"FROM", RESERVED_FROM}},
        {"if", {"IF", RESERVED_IF}},
        {"import", {"IMPORT", RESERVED_IMPORT}},
        {"inline", {"INLINE", RESERVED_INLINE}},
        {"int", {"INT", RESERVED_INT}},
        {"long", {"LONG", RESERVED_LONG}},
        {"module", {"MODULE", RESERVED_MODULE}},
        {"mutable", {"MUTABLE", RESERVED_MUTABLE}},
        {"namespace", {"NAMESPACE", RESERVED_NAMESPACE}},
        {"new", {"NEW", RESERVED_NEW}},
        {"nil", {"NIL", RESERVED_NIL}},
        {"not", {"NOT", RESERVED_NOT}},
        {"noexcept", {"NOEXCEPT", RESERVED_NOEXCEPT}},
        {"nullptr", {"NULLPTR", RESERVED_NULLPTR}},
        {"or", {"OR", RESERVED_OR}},
        {"override", {"OVERRIDE", RESERVED_OVERRIDE}},
        {"print", {"PRINT", RESERVED_PRINT}},
        {"private", {"PRIVATE", RESERVED_PRIVATE}},
        {"protected", {"PROTECTED", RESERVED_PROTECTED}},
        {"public", {"PUBLIC", RESERVED_PUBLIC}},
        {"register", {"REGISTER", RESERVED_REGISTER}},
        {"reinterpret_cast", {"REINTERPRET_CAST", RESERVED_REINTERPRET_CAST}},
        {"requires", {"REQUIRES", RESERVED_REQUIRES}},
        {"return", {"RETURN", RESERVED_RETURN}},
        {"short", {"SHORT", RESERVED_SHORT}},
        {"signed", {"SIGNED", RESERVED_SIGNED}},
        {"static", {"STATIC", RESERVED_STATIC}},
        {"static_cast", {"STATIC_CAST", RESERVED_STATIC_CAST}},
        {"str", {"STR", RESERVED_STR}},
        {"struct", {"STRUCT", RESERVED_STRUCT}},
        {"super", {"SUPER", RESERVED_SUPER}},
        {"switch", {"SWITCH", RESERVED_SWITCH}},
        {"template", {"TEMPLATE", RESERVED_TEMPLATE}},
        {"this", {"THIS", RESERVED_THIS}},
        {"thread_local", {"THREAD_LOCAL", RESERVED_THREAD_LOCAL}},
        {"true", {"TRUE", RESERVED_TRUE}},
        {"try", {"TRY", RESERVED_TRY}},
        {"typename", {"TYPENAME", RESERVED_TYPENAME}},
        {"typeof", {"TYPEOF", RESERVED_TYPEOF}},
        {"union", {"UNION", RESERVED_UNION}},
        {"unsigned", {"UNSIGNED", RESERVED_UNSIGNED}},
        {"virtual", {"VIRTUAL", RESERVED_VIRTUAL}},
        {"void", {"VOID", RESERVED_VOID}},
        {"volatile", {"VOLATILE", RESERVED_VOLATILE}},
        {"while", {"WHILE", RESERVED_WHILE}},
        {"with", {"WITH", RESERVED_WITH}}
    }; // Map of reserved words and their types
};
