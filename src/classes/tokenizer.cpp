#include "tokenizer.h"

// Default constructor implementation
CodeTokenizer::CodeTokenizer() :
    line_num(0),
    mode(NONE),
    err_present(false),
    left_dp(true),
    last_tok(""),
    strValue(""),
    intValue(0),
    floatValue(0.),
    identifierName(""),
    reservedName({ "", NONE }),
    terminator_char('"'),
    tokenizeStatus(0),
    err_type(NONE),
    debug(false),
    additionalErrorInfo("") {
}

// Constructor with debug mode implementation
CodeTokenizer::CodeTokenizer(bool debug) :
    line_num(0),
    mode(NONE),
    err_present(false),
    left_dp(true),
    last_tok(""),
    strValue(""),
    intValue(0),
    floatValue(0.),
    identifierName(""),
    reservedName({ "", NONE }),
    terminator_char('"'),
    tokenizeStatus(0),
    err_type(NONE),
    debug(debug),
    additionalErrorInfo("") {
}

// Destructor implementation
CodeTokenizer::~CodeTokenizer() {
}

// Tokenization function that processes the entire file contents
int CodeTokenizer::tokenize(std::string& file_contents, std::vector<std::pair<std::string, int>>& tokens, ErrHandler& err) {
    // Tokenize the newline character
    tokenizeStatus = tokenizeLoop('\n', tokens);
    if (tokenizeStatus != NONE) {
        err.printErr(tokenizeStatus, line_num, additionalErrorInfo);
        errors.push_back(tokenizeStatus);
    }

    // Process each character in the file contents
    for (char& c : file_contents) {
        tokenizeStatus = tokenizeLoop(c, tokens);
        if (tokenizeStatus != NONE) {
            if (!additionalErrorInfo.empty()) {
                err.printErr(tokenizeStatus, line_num, additionalErrorInfo);
            } else {
                err.printErr(tokenizeStatus, line_num);
            }
            errors.push_back(tokenizeStatus);
        }
    }

    // Tokenize the end of file
    tokenizeStatus = tokenizeLoop(EOF, tokens);
    if (tokenizeStatus != NONE) {
        err.printErr(tokenizeStatus, line_num, additionalErrorInfo);
        errors.push_back(tokenizeStatus);
    }

    // Return -1 if there were errors, otherwise return 0
    if (!errors.empty()) {
        return -1;
    } else {
        return 0;
    }
}

// Helper function to process each character and generate tokens
int CodeTokenizer::tokenizeLoop(char c, std::vector<std::pair<std::string, int>>& tokens) {
    // Handle end of file
    if (c == EOF) {
        CodeTokenizer::tokenizeLoop('\n', tokens);
        if (debug) {
            std::cout << "EOF  null" << std::endl;
        }
        return 0;
    }
    additionalErrorInfo = "";
    err_type = NONE;

    // Switch based on the current mode of the tokenizer
    switch (mode) {
    case INLINE_COMMENT:
        // Handle inline comments
        if (c == '\n') {
            mode = NONE;
            last_tok = "\n";
            tokens.push_back({ last_tok, line_num });
            if (debug) {
                std::cout << "NEW_LINE \\n null" << std::endl;
            }
            line_num++;
        }
        break;
    case STR_LITERAL:
        // Handle string literals
        if (c == terminator_char) {
            mode = NONE;
            last_tok += c;
            if (debug) {
                if ((terminator_char == '\'') && (strValue.size() == 1)) {
                    std::cout << "CHAR " << last_tok << " " << strValue << std::endl;
                }
                std::cout << "STRING " << last_tok << " " << strValue << std::endl;
            }
            tokens.push_back({ last_tok, STRING_TOK });
            last_tok = "";
        } else if (c == '\n') {
            line_num++;
            err_present = true;
            err_type = UNTERMINATED_STR;
            mode = NONE;
        } else {
            last_tok += c;
            strValue += c;
        }
        break;
    case IDENTIFIER:
    case NUM_LITERAL:
        // Handle numeric literals
        if (mode == NUM_LITERAL) {
            if (left_dp) {
                if (isdigit(c)) {
                    last_tok += c;
                    break;
                } else if (c == '.') {
                    left_dp = false;
                    last_tok += c;
                    break;
                } else {
                    mode = NONE;
                    intValue = std::stoi(last_tok);
                    if (debug) {
                        std::cout << "INTEGER " << last_tok << " " << intValue << std::endl;
                    }
                    tokens.push_back({ last_tok, INT_TOK });
                    last_tok = "";
                }
            } else {
                if (isdigit(c)) {
                    last_tok += c;
                    break;
                } else {
                    mode = NONE;
                    floatValue = std::stof(last_tok);
                    if (debug) {
                        std::cout << "FLOAT " << last_tok << " " << floatValue << std::endl;
                    }
                    tokens.push_back({ last_tok, FLOAT_TOK });
                    last_tok = "";
                }
            }
        } else if (mode == IDENTIFIER) {
            // Handle identifiers and reserved keywords
            if ((isdigit(c)) || ((bool)isalpha(c)) || (c == '_')) {
                last_tok += c;
                break;
            } else {
                mode = NONE;

                identifierName = last_tok;

                // Check if the identifier is a reserved keyword
                if (identifierName == "and") {
                    reservedName = { "AND", RESERVED_AND };
                } else if (identifierName == "or") {
                    reservedName = { "OR", RESERVED_OR };
                } else if (identifierName == "if") {
                    reservedName = { "IF", RESERVED_IF };
                } else if (identifierName == "else") {
                    reservedName = { "ELSE", RESERVED_ELSE };
                } else if (identifierName == "class") {
                    reservedName = { "CLASS", RESERVED_CLASS };
                } else if (identifierName == "public") {
                    reservedName = { "PUBLIC", RESERVED_PUBLIC };
                } else if (identifierName == "private") {
                    reservedName = { "PRIVATE", RESERVED_PRIVATE };
                } else if (identifierName == "protected") {
                    reservedName = { "PROTECTED", RESERVED_PROTECTED };
                } else if (identifierName == "nil") {
                    reservedName = { "NIL", RESERVED_NIL };
                } else if (identifierName == "for") {
                    reservedName = { "FOR", RESERVED_FOR };
                } else if (identifierName == "while") {
                    reservedName = { "WHILE", RESERVED_WHILE };
                } else if (identifierName == "continue") {
                    reservedName = { "CONTINUE", RESERVED_CONTINUE };
                } else if (identifierName == "break") {
                    reservedName = { "BREAK", RESERVED_BREAK };
                } else if (identifierName == "print") {
                    reservedName = { "PRINT", RESERVED_PRINT };
                } else if (identifierName == "super") {
                    reservedName = { "SUPER", RESERVED_SUPER };
                } else if (identifierName == "this") {
                    reservedName = { "THIS", RESERVED_THIS };
                } else if (identifierName == "return") {
                    reservedName = { "RETURN", RESERVED_RETURN };
                } else if (identifierName == "void") {
                    reservedName = { "VOID", RESERVED_VOID };
                } else if (identifierName == "struct") {
                    reservedName = { "STRUCT", RESERVED_STRUCT };
                } else if (identifierName == "enum") {
                    reservedName = { "ENUM", RESERVED_ENUM };
                } else if (identifierName == "UNION") {
                    reservedName = { "UNION", RESERVED_UNION };
                } else if (identifierName == "int") {
                    reservedName = { "INT", RESERVED_INT };
                } else if (identifierName == "long") {
                    reservedName = { "LONG", RESERVED_LONG };
                } else if (identifierName == "short") {
                    reservedName = { "SHORT", RESERVED_SHORT };
                } else if (identifierName == "signed") {
                    reservedName = { "SIGNED", RESERVED_SIGNED };
                } else if (identifierName == "unsigned") {
                    reservedName = { "UNSIGNED", RESERVED_UNSIGNED };
                } else if (identifierName == "float") {
                    reservedName = { "FLOAT", RESERVED_FLOAT };
                } else if (identifierName == "double") {
                    reservedName = { "DOUBLE", RESERVED_DOUBLE };
                } else if (identifierName == "char") {
                    reservedName = { "CHAR", RESERVED_CHAR };
                } else if (identifierName == "str") {
                    reservedName = { "STR", RESERVED_STR };
                } else if (identifierName == "bool") {
                    reservedName = { "BOOL", RESERVED_BOOL };
                } else if (identifierName == "true") {
                    reservedName = { "TRUE", RESERVED_TRUE };
                } else if (identifierName == "false") {
                    reservedName = { "FALSE", RESERVED_FALSE };
                } else if (identifierName == "switch") {
                    reservedName = { "SWITCH", RESERVED_SWITCH };
                } else if (identifierName == "case") {
                    reservedName = { "CASE", RESERVED_CASE };
                } else if (identifierName == "default") {
                    reservedName = { "DEFAULT", RESERVED_DEFAULT };
                } else if (identifierName == "delete") {
                    reservedName = { "DELETE", RESERVED_DELETE };
                } else if (identifierName == "mutable") {
                    reservedName = { "MUTABLE", RESERVED_MUTABLE };
                } else if (identifierName == "const") {
                    reservedName = { "CONST", RESERVED_CONST };
                } else if (identifierName == "constexpr") {
                    reservedName = { "CONSTEXPR", RESERVED_CONSTEXPR };
                } else if (identifierName == "friend") {
                    reservedName = { "FRIEND", RESERVED_FRIEND };
                } else if (identifierName == "virtual") {
                    reservedName = { "VIRTUAL", RESERVED_VIRTUAL };
                } else if (identifierName == "final") {
                    reservedName = { "FINAL", RESERVED_FINAL };
                } else if (identifierName == "override") {
                    reservedName = { "OVERRIDE", RESERVED_OVERRIDE };
                } else if (identifierName == "protected") {
                    reservedName = { "PROTECTED", RESERVED_PROTECTED };
                } else if (identifierName == "new") {
                    reservedName = { "NEW", RESERVED_NEW };
                } else if (identifierName == "namespace") {
                    reservedName = { "NAMESPACE", RESERVED_NAMESPACE };
                } else if (identifierName == "typeof") {
                    reservedName = { "TYPEOF", RESERVED_TYPEOF };
                } else if (identifierName == "assert") {
                    reservedName = { "ASSERT", RESERVED_ASSERT };
                } else if (identifierName == "template") {
                    reservedName = { "TEMPLATE", RESERVED_TEMPLATE };
                } else if (identifierName == "typename") {
                    reservedName = { "TYPENAME", RESERVED_TYPENAME };
                } else if (identifierName == "register") {
                    reservedName = { "REGISTER", RESERVED_REGISTER };
                } else if (identifierName == "volatile") {
                    reservedName = { "VOLATILE", RESERVED_VOLATILE };
                } else if (identifierName == "static") {
                    reservedName = { "STATIC", RESERVED_STATIC };
                } else if (identifierName == "inline") {
                    reservedName = { "INLINE", RESERVED_INLINE };
                } else if (identifierName == "alignas") {
                    reservedName = { "ALIGNAS", RESERVED_ALIGNAS };
                } else if (identifierName == "alignof") {
                    reservedName = { "ALIGNOF", RESERVED_ALIGNOF };
                } else if (identifierName == "noexcept") {
                    reservedName = { "NOEXCEPT", RESERVED_NOEXCEPT };
                } else if (identifierName == "decltype") {
                    reservedName = { "DECLTYPE", RESERVED_DECLTYPE };
                } else if (identifierName == "nullptr") {
                    reservedName = { "NULLPTR", RESERVED_NULLPTR };
                } else if (identifierName == "thread_local") {
                    reservedName = { "THREAD_LOCAL", RESERVED_THREAD_LOCAL };
                } else if (identifierName == "static_cast") {
                    reservedName = { "STATIC_CAST", RESERVED_STATIC_CAST };
                } else if (identifierName == "dynamic_cast") {
                    reservedName = { "DYNAMIC_CAST", RESERVED_DYNAMIC_CAST };
                } else if (identifierName == "reinterpret_cast") {
                    reservedName = { "REINTERPRET_CAST", RESERVED_REINTERPRET_CAST };
                } else if (identifierName == "const_cast") {
                    reservedName = { "CONST_CAST", RESERVED_CONST_CAST };
                } else if (identifierName == "try") {
                    reservedName = { "TRY", RESERVED_TRY };
                } else if (identifierName == "catch") {
                    reservedName = { "CATCH", RESERVED_CATCH };
                } else if (identifierName == "explicit") {
                    reservedName = { "EXPLICIT", RESERVED_EXPLICIT };
                } else if (identifierName == "export") {
                    reservedName = { "EXPORT", RESERVED_EXPORT };
                } else if (identifierName == "import") {
                    reservedName = { "IMPORT", RESERVED_IMPORT };
                } else if (identifierName == "module") {
                    reservedName = { "MODULE", RESERVED_MODULE };
                } else if (identifierName == "requires") {
                    reservedName = { "REQUIRES", RESERVED_REQUIRES };
                } else if (identifierName == "with") {
                    reservedName = { "WITH", RESERVED_WITH };
                } else if (identifierName == "from") {
                    reservedName = { "FROM", RESERVED_FROM };
                } else {
                    reservedName = { "IDENTIFIER", RESERVED_IDENTIFIER };
                }
                if (debug) {
                    std::cout << reservedName.first << " " << identifierName << " null" << std::endl;
                }
                tokens.push_back({ last_tok, reservedName.second });
                last_tok = "";
            }
        }
    case NONE:
        // Handle various operators and symbols
        if (c == '=') {
            if (last_tok == "=") {
                if (debug) {
                    std::cout << "EQUAL_EQUAL == null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return 0;
            } else if (last_tok == "!") {
                if (debug) {
                    std::cout << "BANG_EQUAL != null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return 0;
            } else if (last_tok == "<") {
                if (debug) {
                    std::cout << "LESS_EQUAL <= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return 0;
            } else if (last_tok == ">") {
                if (debug) {
                    std::cout << "GREATER_EQUAL >= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return 0;
            } else if (last_tok == "+") {
                if (debug) {
                    std::cout << "PLUS_EQUAL += null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ASSIGNMENT_TOK });
                last_tok = "";
                return 0;
            } else if (last_tok == "-") {
                if (debug) {
                    std::cout << "MINUS_EQUAL -= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ASSIGNMENT_TOK });
                last_tok = "";
                return 0;
            } else if (last_tok == "/") {
                if (debug) {
                    std::cout << "DIVIDE_EQUAL /= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ASSIGNMENT_TOK });
                last_tok = "";
                return 0;
            } else if (last_tok == "*") {
                if (debug) {
                    std::cout << "TIMES_EQUAL *= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ASSIGNMENT_TOK });
                last_tok = "";
                return 0;
            }
        } else if (last_tok == "=") {
            if (debug) {
                std::cout << "EQUAL = null" << std::endl;
            }
            tokens.push_back({ last_tok, ASSIGNMENT_TOK });
        } else if (last_tok == "!") {
            if (debug) {
                std::cout << "BANG ! null" << std::endl;
            }
            tokens.push_back({ last_tok, LOGICAL_OPERATOR_TOK });
        } else if (last_tok == "<") {
            if (c == '<') {
                if (debug) {
                    std::cout << "LEFT_SHIFT << null" << std::endl;
                }
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return 0;
            } else {
                if (debug) {
                    std::cout << "LESS < null" << std::endl;
                }
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
            }
        } else if (last_tok == ">") {
            if (c == '>') {
                if (debug) {
                    std::cout << "RIGHT_SHIFT >> null" << std::endl;
                }
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return 0;
            } else {
                if (debug) {
                    std::cout << "GREATER > null" << std::endl;
                }
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
            }
        } else if (last_tok == "+") {
            if (debug) {
                std::cout << "PLUS + null" << std::endl;
            }
            tokens.push_back({ last_tok, MATHEMATICAL_OPERATOR_TOK });
        } else if (last_tok == "-") {
            if (debug) {
                std::cout << "MINUS - null" << std::endl;
            }
            tokens.push_back({ last_tok, MATHEMATICAL_OPERATOR_TOK });
        } else if (last_tok == "*") {
            if (debug) {
                std::cout << "STAR * null" << std::endl;
            }
            tokens.push_back({ last_tok, STAR_TOK });
        }
        if (c == '/') {
            if (last_tok == "/") {
                mode = INLINE_COMMENT; // Start inline comment mode
                last_tok = "";
                return 0;
            }
        } else if (last_tok == "/") {
            if (debug) {
                std::cout << "SLASH / null" << std::endl;
            }
            tokens.push_back({ last_tok, MATHEMATICAL_OPERATOR_TOK });
        }
        if (c == '|') {
            if (last_tok == "|") {
                if (debug) {
                    std::cout << "BAR_BAR || null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, LOGICAL_OPERATOR_TOK });
                last_tok = "";
                return 0;
            }
        } else if (last_tok == "|") {
            if (debug) {
                std::cout << "BAR | null" << std::endl;
            }
            tokens.push_back({ last_tok, LOGICAL_OPERATOR_TOK });
        }
        if (c == '&') {
            if (last_tok == "&") {
                if (debug) {
                    std::cout << "AND_AND && null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, LOGICAL_OPERATOR_TOK });
                last_tok = "";
                return 0;
            }
        } else if (last_tok == "&") {
            if (debug) {
                std::cout << "AND & null" << std::endl;
            }
            tokens.push_back({ last_tok, LOGICAL_OPERATOR_TOK });
        }
        if (isdigit(c)) {
            mode = NUM_LITERAL; // Switch to numeric literal mode
            left_dp = true; // Reset decimal point flag
            last_tok = "";
            last_tok += c; // Start building the number
        } else if ((bool)isalpha(c) || c == '_') {
            mode = IDENTIFIER; // Switch to identifier mode
            last_tok = "";
            last_tok += c; // Start building the identifier
        }

        last_tok = "";
        last_tok += c; // Add the current character to the last token

        // Handle specific characters and their corresponding tokens
        switch (c) {
        case '=':
            last_tok = "=";
            break;
        case '!':
            last_tok = "!";
            break;
        case '<':
            last_tok = "<";
            break;
        case '>':
            last_tok = ">";
            break;
        case '/':
            last_tok = "/";
            break;
        case '+':
            last_tok = "+";
            break;
        case '-':
            last_tok = "-";
            break;
        case '*':
            last_tok = "*";
            break;
        case '|':
            last_tok = "|";
            break;
        case '&':
            last_tok = "&";
            break;
        case ' ': break; // Ignore spaces
        case '\t': break; // Ignore tabs
        case '\n':
            if (debug) {
                std::cout << "NEW_LINE \\n null" << std::endl;
            }
            line_num++; // Increment line number
            last_tok = "\n";
            tokens.push_back({ last_tok, line_num });
            break;
        case '(':
            last_tok = "(";
            tokens.push_back({ last_tok, CONTEXT_TOK });
            if (debug) {
                std::cout << "LEFT_PAREN ( null" << std::endl;
            }
            break;
        case ')':
            last_tok = ")";
            tokens.push_back({ last_tok, CONTEXT_TOK });
            if (debug) {
                std::cout << "RIGHT_PAREN ) null" << std::endl;
            }
            break;
        case '{':
            last_tok = "{";
            tokens.push_back({ last_tok, CONTEXT_TOK });
            if (debug) {
                std::cout << "LEFT_BRACE { null" << std::endl;
            }
            break;
        case '}':
            last_tok = "}";
            tokens.push_back({ last_tok, CONTEXT_TOK });
            if (debug) {
                std::cout << "RIGHT_BRACE } null" << std::endl;
            }
            break;
        case ',':
            last_tok = ",";
            tokens.push_back({ last_tok, SEPARATOR_TOK });
            if (debug) {
                std::cout << "COMMA , null" << std::endl;
            }
            break;
        case '.':
            last_tok = ".";
            tokens.push_back({ last_tok, ACCESS_TOK });
            if (debug) {
                std::cout << "DOT . null" << std::endl;
            }
            break;
        case ';':
            last_tok = ";";
            tokens.push_back({ last_tok, TERMINATOR_TOK });
            if (debug) {
                std::cout << "SEMICOLON ; null" << std::endl;
            }
            break;
        case ':':
            last_tok = ":";
            tokens.push_back({ last_tok, CONTEXT_TOK });
            if (debug) {
                std::cout << "COLON : null" << std::endl;
            }
            break;
        case '%':
            last_tok = "%";
            tokens.push_back({ last_tok, MATHEMATICAL_OPERATOR_TOK });
            if (debug) {
                std::cout << "MODULO % null" << std::endl;
            }
            break;
        case '\\':
            last_tok = "\\";
            tokens.push_back({ last_tok, TERMINATOR_TOK });
            if (debug) {
                std::cout << "BACK_SLASH \\ null" << std::endl;
            }
            break;
        case '?':
            last_tok = "?";
            tokens.push_back({ last_tok, TERNARY_TOK });
            if (debug) {
                std::cout << "QUESTION ? null" << std::endl;
            }
            break;
        case '#':
            last_tok = "#";
            tokens.push_back({ last_tok, ACTION_TOK });
            if (debug) {
                std::cout << "HASH_TAG # null" << std::endl;
            }
            break;
        case '^':
            last_tok = "^";
            tokens.push_back({ last_tok, LOGICAL_OPERATOR_TOK });
            if (debug) {
                std::cout << "XOR ^ null" << std::endl;
            }
            break;
        case '~':
            last_tok = "~";
            tokens.push_back({ last_tok, LOGICAL_OPERATOR_TOK });
            if (debug) {
                std::cout << "TILDE ~ null" << std::endl;
            }
            break;
        case '"':
            last_tok = "\"";
            mode = STR_LITERAL; // Switch to string literal mode
            terminator_char = '"'; // Set terminator character
            strValue = ""; // Reset string value
            break;
        case '\'':
            last_tok = "'";
            mode = STR_LITERAL; // Switch to string literal mode
            terminator_char = '\''; // Set terminator character
            strValue = ""; // Reset string value
            break;
        default:
            // Handle unexpected characters
            if ((isdigit(c)) || ((bool)isalpha(c)) || (c == '_')) {
                break;
            }
            last_tok = "";
            err_present = true; // Set error flag
            err_type = UNEXPECTED_CHAR; // Set error type
            additionalErrorInfo += c; // Add unexpected character to error info
            break;
        }
        break;
    }

    return err_type; // Return the error type
}