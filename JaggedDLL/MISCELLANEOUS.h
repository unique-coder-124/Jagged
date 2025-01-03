#pragma once

#include <unordered_map>
#include <utility>
#include <string>
#include <vector>
#include <memory>

#pragma region ContextTypes
#define GLOBAL_CONTEXT 1
#define GENERIC_CONTEXT 2
#define OBJASSIGNMENT_CONTEXT 3
#define CLASS_CONTEXT 4
#define STRUCT_CONTEXT 5
#define FUNCTION_CONTEXT 6
#define LOOP_CONTEXT 7
#define CONDITIONAL_CONTEXT 8
#pragma endregion

namespace JaggedTypes {
	struct Context;
	struct Function;
	using Class = Context;
	using Struct = Context;
	typedef std::pair<std::string, int> Token;
	typedef std::vector<Token> Expression;
	typedef std::vector<Token> TokenArr;
	typedef std::vector<Expression> Expressions;

	struct Context {
		Context() : type(GENERIC_CONTEXT), Parent(nullptr) {}
		Context(int type) : type(type), Parent(nullptr) {}
		Context(Context* Parent) : type(GENERIC_CONTEXT), Parent(Parent) {}
		Context(int type, Context* Parent) : type(type), Parent(Parent) {}

		int type;

		Context* Parent;

		Expressions Code;

		std::unordered_map<std::string, Context> Children;

		std::unordered_map<std::string, Function> Functions;
		std::unordered_map<std::string, Class> Classes;
		std::unordered_map<std::string, Struct> Structs;
		std::unordered_map<std::string, std::pair<Token, std::shared_ptr<void>>> Variables;

		// Destructor
		~Context() {
			// Clear all children
			for (auto& child : Children) {
				child.second.~Context(); // Call destructor for each child explicitly
			}
			Children.clear();

			// Clear all functions
			Functions.clear(); // Function destructor handles cleanup of nested Scopes

			// Clear all classes (Class is typedef of Context)
			for (auto& cls : Classes) {
				cls.second.~Context(); // Recursively call destructor for each class
			}
			Classes.clear();

			// Clear all structs (Struct is typedef of Context)
			for (auto& strct : Structs) {
				strct.second.~Context(); // Recursively call destructor for each struct
			}
			Structs.clear();

			// Clear all variables
			Variables.clear(); // std::shared_ptr automatically cleans up memory
		}
	};

	struct Function {
		Token ReturnType;
		TokenArr Args;

		Context Scope;

		// Destructor
		~Function() {
			// The `Scope` will clean up its nested data with its destructor
		}
	};
}
