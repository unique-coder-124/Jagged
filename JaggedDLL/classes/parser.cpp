#include "parser.h"

// Default constructor implementation
CodeParser::CodeParser() :
	mode(NONE),
	line_num(0),
	err_present(false),
	parseStatus(NONE),
	err_type(NONE),
	debug(false) {
}

// Constructor with debug mode implementation
CodeParser::CodeParser(bool debug) :
	mode(NONE),
	line_num(0),
	err_present(false),
	parseStatus(0),
	err_type(NONE),
	debug(debug) {
}

// Destructor implementation
CodeParser::~CodeParser() {
}

int CodeParser::parse(JaggedTypes::TokenArr& tokens, JaggedTypes::Context ContextHead, ErrHandler& err){
	for (int token_idx = 0; token_idx < tokens.size(); token_idx++) {
		parseStatus = parseLoop(token_idx, tokens, ContextHead);
		if (parseStatus != NONE) {
			if (!additionalErrorInfo.empty()) {
				err.printErr(parseStatus, line_num, additionalErrorInfo);
			} else {
				err.printErr(parseStatus, line_num);
			}
		}
	}

	if (err_present) {
		return ERROR_OCCURED_IN_PARSING;
	} else {
		return NONE;
	}
}

// Helper function to process each token and generate parsed output
int CodeParser::parseLoop(int token_idx, JaggedTypes::TokenArr& tokens, JaggedTypes::Context ContextNode) {
	additionalErrorInfo = "";
	err_type = NONE;
	
	// Switch based on the current mode of the parser
	switch (mode) {
	case NONE:
		if (tokens[token_idx].first == "\n") {
			line_num++;
			break;
		}
		switch (tokens[token_idx].second) {
		case ACCESS_TOK:
			// TODO
			break;
		case ACTION_TOK:
			// TODO
			break;
		case ARROW_TOK:
			// TODO
			break;
		case ASSIGNMENT_TOK:
			// TODO
			break;
		case CHAR_TOK:
			// TODO
			break;
		case CONTEXT_TOK:
			// TODO
			break;
		case DECREMENT_TOK:
			// TODO
			break;
		case DOUBLE_TOK:
			// TODO
			break;
		case EQUALITY_OPERATOR_TOK:
			// TODO
			break;
		case FLOAT_TOK:
			// TODO
			break;
		case IDENTIFIER_TOK:
			// TODO
			break;
		case INCREMENT_TOK:
			// TODO
			break;
		case INT_TOK:
			// TODO
			break;
		case LOGICAL_OPERATOR_TOK:
			// TODO
			break;
		case MATHEMATICAL_OPERATOR_TOK:
			// TODO
			break;
		case POST_DECREMENT_TOK:
			// TODO
			break;
		case POST_INCREMENT_TOK:
			// TODO
			break;
		case PRE_DECREMENT_TOK:
			// TODO
			break;
		case PRE_INCREMENT_TOK:
			// TODO
			break;
		case SEPARATOR_TOK:
			// TODO
			break;
		case STAR_TOK:
			// TODO
			break;
		case STRING_TOK:
			// TODO
			break;
		case TERMINATOR_TOK:
			// TODO
			break;
		case TERNARY_TOK:
			// TODO
			break;
		default:
			handleReserved(tokens[token_idx]);
			break;
		}
		break;
	}
	return UNIMPLEMENTED;
}

int CodeParser::handleReserved(JaggedTypes::Token token) {
	switch (token.second) {
	case RESERVED_ALIGNAS:
		// TODO
		break;
	case RESERVED_ALIGNOF:
		// TODO
		break;
	case RESERVED_AND:
		// TODO
		break;
	case RESERVED_ASSERT:
		// TODO
		break;
	case RESERVED_BOOL:
		// TODO
		break;
	case RESERVED_BREAK:
		// TODO
		break;
	case RESERVED_CASE:
		// TODO
		break;
	case RESERVED_CATCH:
		// TODO
		break;
	case RESERVED_CHAR:
		// TODO
		break;
	case RESERVED_CLASS:
		// TODO
		break;
	case RESERVED_CONST:
		// TODO
		break;
	case RESERVED_CONSTEXPR:
		// TODO
		break;
	case RESERVED_CONST_CAST:
		// TODO
		break;
	case RESERVED_CONTINUE:
		// TODO
		break;
	case RESERVED_DECLTYPE:
		// TODO
		break;
	case RESERVED_DEFAULT:
		// TODO
		break;
	case RESERVED_DELETE:
		// TODO
		break;
	case RESERVED_DOUBLE:
		// TODO
		break;
	case RESERVED_DYNAMIC_CAST:
		// TODO
		break;
	case RESERVED_ELSE:
		// TODO
		break;
	case RESERVED_ENUM:
		// TODO
		break;
	case RESERVED_EXPLICIT:
		// TODO
		break;
	case RESERVED_EXPORT:
		// TODO
		break;
	case RESERVED_FALSE:
		// TODO
		break;
	case RESERVED_FINAL:
		// TODO
		break;
	case RESERVED_FLOAT:
		// TODO
		break;
	case RESERVED_FOR:
		// TODO
		break;
	case RESERVED_FRIEND:
		// TODO
		break;
	case RESERVED_FROM:
		// TODO
		break;
	case RESERVED_IDENTIFIER:
		// TODO
		break;
	case RESERVED_IF:
		// TODO
		break;
	case RESERVED_IMPORT:
		// TODO
		break;
	case RESERVED_INLINE:
		// TODO
		break;
	case RESERVED_INT:
		// TODO
		break;
	case RESERVED_LONG:
		// TODO
		break;
	case RESERVED_MODULE:
		// TODO
		break;
	case RESERVED_MUTABLE:
		// TODO
		break;
	case RESERVED_NAMESPACE:
		// TODO
		break;
	case RESERVED_NEW:
		// TODO
		break;
	case RESERVED_NIL:
		// TODO
		break;
	case RESERVED_NOEXCEPT:
		// TODO
		break;
	case RESERVED_NOT:
		// TODO
		break;
	case RESERVED_NULLPTR:
		// TODO
		break;
	case RESERVED_OR:
		// TODO
		break;
	case RESERVED_OVERRIDE:
		// TODO
		break;
	case RESERVED_PRINT:
		// TODO
		break;
	case RESERVED_PRIVATE:
		// TODO
		break;
	case RESERVED_PROTECTED:
		// TODO
		break;
	case RESERVED_PUBLIC:
		// TODO
		break;
	case RESERVED_REGISTER:
		// TODO
		break;
	case RESERVED_REINTERPRET_CAST:
		// TODO
		break;
	case RESERVED_REQUIRES:
		// TODO
		break;
	case RESERVED_RETURN:
		// TODO
		break;
	case RESERVED_SHORT:
		// TODO
		break;
	case RESERVED_SIGNED:
		// TODO
		break;
	case RESERVED_STATIC:
		// TODO
		break;
	case RESERVED_STATIC_CAST:
		// TODO
		break;
	case RESERVED_STR:
		// TODO
		break;
	case RESERVED_STRUCT:
		// TODO
		break;
	case RESERVED_SUPER:
		// TODO
		break;
	case RESERVED_SWITCH:
		// TODO
		break;
	case RESERVED_TEMPLATE:
		// TODO
		break;
	case RESERVED_THIS:
		// TODO
		break;
	case RESERVED_THREAD_LOCAL:
		// TODO
		break;
	case RESERVED_TRUE:
		// TODO
		break;
	case RESERVED_TRY:
		// TODO
		break;
	case RESERVED_TYPENAME:
		// TODO
		break;
	case RESERVED_TYPEOF:
		// TODO
		break;
	case RESERVED_UNION:
		// TODO
		break;
	case RESERVED_UNSIGNED:
		// TODO
		break;
	case RESERVED_VIRTUAL:
		// TODO
		break;
	case RESERVED_VOID:
		// TODO
		break;
	case RESERVED_VOLATILE:
		// TODO
		break;
	case RESERVED_WHILE:
		// TODO
		break;
	case RESERVED_WITH:
		// TODO
		break;
	default:
		return UNIMPLEMENTED;
	}
	return UNIMPLEMENTED;
}

// Fast check for digit characters
bool CodeParser::isDigitFast(char c) {
	return (c >= '0' && c <= '9');
}

// Fast check for alphabetic characters
bool CodeParser::isAlphaFast(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}