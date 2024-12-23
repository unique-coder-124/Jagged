#pragma once


#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_PATCH 2


#define NONE 0

#pragma region tokenizer_modes
#define INLINE_COMMENT 1
#define BLOCK_COMMENT 2
#define STR_LITERAL 3
#define CHAR_LITERAL 4
#define NUM_LITERAL 5
#define INT_LITERAL 5
#define FLOAT_LITERAL 5
#define DOUBLE_LITERAL 5
#define IDENTIFIER 6
#pragma endregion

#pragma region token_types
#define INT_TOK 1
#define FLOAT_TOK 2
#define DOUBLE_TOK 3
#define IDENTIFIER_TOK 4
#define STRING_TOK 5
#define CHAR_TOK 6
#define EQUALITY_OPERATOR_TOK 7
#define LOGICAL_OPERATOR_TOK 8
#define MATHEMATICAL_OPERATOR_TOK 9
#define CONTEXT_TOK 10
#define ASSIGNMENT_TOK 11
#define STAR_TOK 12
#define TERNARY_TOK 13
#define SEPARATOR_TOK 14
#define TERMINATOR_TOK 15
#define ACCESS_TOK 16
#define ACTION_TOK 17
#define DECREMENT_TOK 18
#define INCREMENT_TOK 19
#define PRE_DECREMENT_TOK 20
#define POST_DECREMENT_TOK 21
#define PRE_INCREMENT_TOK 22
#define POST_INCREMENT_TOK 23
#define ARROW_TOK 24

#define RESERVED_AND 25
#define RESERVED_OR 26
#define RESERVED_IF 27
#define RESERVED_ELSE 28
#define RESERVED_CLASS 29
#define RESERVED_NIL 30
#define RESERVED_FOR 31
#define RESERVED_WHILE 32
#define RESERVED_PRINT 33
#define RESERVED_SUPER 34
#define RESERVED_THIS 35
#define RESERVED_RETURN 36
#define RESERVED_VOID 37
#define RESERVED_STRUCT 38
#define RESERVED_ENUM 39
#define RESERVED_INT 40
#define RESERVED_FLOAT 41
#define RESERVED_DOUBLE 42
#define RESERVED_CHAR 43
#define RESERVED_STR 44
#define RESERVED_BOOL 45
#define RESERVED_TRUE 46
#define RESERVED_FALSE 47
#define RESERVED_IDENTIFIER 48
#define RESERVED_PUBLIC 49
#define RESERVED_PRIVATE 50
#define RESERVED_PROTECTED 51
#define RESERVED_CONTINUE 52
#define RESERVED_BREAK 53
#define RESERVED_UNION 54
#define RESERVED_LONG 55
#define RESERVED_SHORT 56
#define RESERVED_SIGNED 57
#define RESERVED_UNSIGNED 58
#define RESERVED_SWITCH 59
#define RESERVED_CASE 60
#define RESERVED_DEFAULT 61
#define RESERVED_DELETE 62
#define RESERVED_MUTABLE 63
#define RESERVED_CONST 64
#define RESERVED_CONSTEXPR 65
#define RESERVED_FRIEND 66
#define RESERVED_VIRTUAL 67
#define RESERVED_FINAL 68
#define RESERVED_OVERRIDE 69
#define RESERVED_NEW 70
#define RESERVED_NAMESPACE 71
#define RESERVED_TYPEOF 72
#define RESERVED_ASSERT 73
#define RESERVED_TEMPLATE 74
#define RESERVED_TYPENAME 75
#define RESERVED_REGISTER 76
#define RESERVED_VOLATILE 77
#define RESERVED_STATIC 78
#define RESERVED_INLINE 79
#define RESERVED_ALIGNAS 80
#define RESERVED_ALIGNOF 81
#define RESERVED_NOEXCEPT 82
#define RESERVED_DECLTYPE 83
#define RESERVED_NULLPTR 84
#define RESERVED_THREAD_LOCAL 85
#define RESERVED_STATIC_CAST 86
#define RESERVED_DYNAMIC_CAST 87
#define RESERVED_REINTERPRET_CAST 88
#define RESERVED_CONST_CAST 89
#define RESERVED_TRY 90
#define RESERVED_CATCH 91
#define RESERVED_EXPLICIT 92
#define RESERVED_EXPORT 93
#define RESERVED_IMPORT 94
#define RESERVED_MODULE 95
#define RESERVED_REQUIRES 96
#define RESERVED_WITH 97
#define RESERVED_FROM 98
#pragma endregion

#pragma region errors
#define FILE_NOT_FOUND 1
#define ERROR_OCCURED 10
#define INVALID_ARGS 28
#define UNTERMINATED_STR 34
#define MALFORMED_CHAR 35
#define UNEXPECTED_CHAR 36
#define UNTERMINATED_PARENTHESES 41
#define ERROR_OCCURED_IN_TOKENIZATION 65
#define ERROR_OCCURED_IN_PARSING 66
#define UNTERMINATED_BRACKET 93
#define UNTERMINATED_BRACE 125
#define UNIMPLIMENTED 255
#pragma endregion

#include <unordered_map>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>