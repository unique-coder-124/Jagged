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

    // Return ERROR_OCCURED_IN_TOKENIZATION if there were errors, otherwise return NONE
    if (!errors.empty()) {
        return ERROR_OCCURED_IN_TOKENIZATION;
    } else {
        return NONE;
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
        return NONE;
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
	case BLOCK_COMMENT:
		// Handle block comments
        if (last_tok == "*" && c == '/') {
            mode = NONE;
            last_tok = "";
		} else {
			last_tok = c;
		}
		break;
	case CHAR_LITERAL:
		// Handle character literals
		if (c == terminator_char) {
			mode = NONE;
			last_tok += c;
			if (strValue.size() > 1) {
				err_present = true;
				err_type = MALFORMED_CHAR;
				additionalErrorInfo = last_tok;
				break;
			} else if (strValue.size() == 0) {
				err_present = true;
				err_type = MALFORMED_CHAR;
                additionalErrorInfo = last_tok;
				break;
			}
			if (debug) {
				std::cout << "CHAR " << last_tok << " " << strValue << std::endl;
            }
			tokens.push_back({ last_tok, CHAR_TOK });
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
                if (isDigitFast(c)) {
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
                if (isDigitFast(c)) {
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
            if ((isDigitFast(c)) || ((bool)isAlphaFast(c)) || (c == '_')) {
                last_tok += c;
                break;
            } else {
                mode = NONE;

                identifierName = last_tok;

                // Check if the identifier is a reserved keyword
                auto it = reservedKeyWords.find(identifierName);
                if (it != reservedKeyWords.end()) {
                    reservedName = it->second;
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
                return NONE;
            } else if (last_tok == "!") {
                if (debug) {
                    std::cout << "BANG_EQUAL != null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return NONE;
            } else if (last_tok == "<") {
                if (debug) {
                    std::cout << "LESS_EQUAL <= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return NONE;
            } else if (last_tok == ">") {
                if (debug) {
                    std::cout << "GREATER_EQUAL >= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, EQUALITY_OPERATOR_TOK });
                last_tok = "";
                return NONE;
            } else if (last_tok == "+") {
                if (debug) {
                    std::cout << "PLUS_EQUAL += null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ASSIGNMENT_TOK });
                last_tok = "";
                return NONE;
            } else if (last_tok == "-") {
                if (debug) {
                    std::cout << "MINUS_EQUAL -= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ASSIGNMENT_TOK });
                last_tok = "";
                return NONE;
            } else if (last_tok == "/") {
                if (debug) {
                    std::cout << "DIVIDE_EQUAL /= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ASSIGNMENT_TOK });
                last_tok = "";
                return NONE;
            } else if (last_tok == "%") {
				if (debug) {
					std::cout << "MOD_EQUAL %= null" << std::endl;
				}
				last_tok += c;
				tokens.push_back({ last_tok, ASSIGNMENT_TOK });
				last_tok = "";
				return NONE;
            } else if (last_tok == "*") {
                if (debug) {
                    std::cout << "TIMES_EQUAL *= null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ASSIGNMENT_TOK });
                last_tok = "";
                return NONE;
            }
		} else if (c == '-') {
            if (last_tok == "-") {
                if (debug) {
                    std::cout << "DECREMENT -- null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, DECREMENT_TOK });
                last_tok = "";
                return NONE;
            }
		} else if (c == '+') {
			if (last_tok == "+") {
				if (debug) {
					std::cout << "INCREMENT ++ null" << std::endl;
				}
				last_tok += c;
				tokens.push_back({ last_tok, INCREMENT_TOK });
				last_tok = "";
				return NONE;
			}
		} else if (c == '>') {
            if (last_tok == "-") {
                if (debug) {
                    std::cout << "ARROW -> null" << std::endl;
                }
                last_tok += c;
                tokens.push_back({ last_tok, ARROW_TOK });
                last_tok = "";
                return NONE;
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
                return NONE;
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
                return NONE;
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
        } else if (last_tok == "%") {
			if (debug) {
				std::cout << "MOD % null" << std::endl;
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
                return NONE;
            } else if (last_tok == "*") {
				mode = BLOCK_COMMENT; // Start block comment mode
				last_tok = "";
				return NONE;
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
                return NONE;
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
                return NONE;
            }
        } else if (last_tok == "&") {
            if (debug) {
                std::cout << "AND & null" << std::endl;
            }
            tokens.push_back({ last_tok, LOGICAL_OPERATOR_TOK });
        }
        if (isDigitFast(c)) {
            mode = NUM_LITERAL; // Switch to numeric literal mode
            left_dp = true; // Reset decimal point flag
            last_tok = "";
            last_tok += c; // Start building the number
        } else if ((bool)isAlphaFast(c) || c == '_') {
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
		case '%':
			last_tok = "%";
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
            mode = CHAR_LITERAL; // Switch to char literal mode
            terminator_char = '\''; // Set terminator character
            strValue = ""; // Reset string value
            break;
        default:
            // Handle unexpected characters
            if ((isDigitFast(c)) || ((bool)isAlphaFast(c)) || (c == '_')) {
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

// Fast check for digit characters
bool CodeTokenizer::isDigitFast(char c) {
	return (c >= '0' && c <= '9');
}

// Fast check for alphabetic characters
bool CodeTokenizer::isAlphaFast(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}