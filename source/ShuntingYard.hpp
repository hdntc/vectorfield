#ifndef SHUNTING_YARD
#define SHUNTING_YARD

#include <vector>
#include <string>
#include <map>
#include <stack>
#include <cmath>

namespace ShuntingYard {
	/*
		Typedefs
	*/

	// RPN list
	typedef std::vector<std::string> RPN;

	// callback to unary function (1 argument)
	typedef double(*UnaryFuncEval)(double x);

	// callback to binary function (2 arguments)
	typedef double(*BinaryFuncEval)(double x, double y);

	// types
	enum class TokenTypes {
		OPERATOR,
		CONSTANT,
		FUNCTION,
		LPAREN,
		RPAREN,
		ELSE
	};

	/*
		Utility function callbacks
	*/

	// determine if vector contains values
	template<typename T>
	bool contains(std::vector<T> v, T x);

	// obtain key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m);

	// obtain combined key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m1, std::map<std::string, T> m2);

	// determine if character is number
	bool isNumber(char c, bool acceptDecimal = true, bool acceptNegative = true);

	// determine if entire string is number
	bool isNumber(const char* str);

	// determine if string only contains numerical characters
	bool containsNumbers(const char* str);

	// get numerical value of string
	double getNumericalVal(const char* str, float x, float y);

	// determine if string matches a function
	bool isFunction(std::string str);

	// determine if function is left associative
	bool isLeftAssociative(std::string str);

	// get function precedence
	short getPrecedence(std::string str);

	// find element from list in the equation starting at index i
	std::string findElement(int i, const char* eqn, std::vector<std::string> list);

	/*
		Function class definition
	*/
	class Func {
	public:
		// default constructor
		Func();

			// constructor for unary functions
		Func(UnaryFuncEval eval, TokenTypes type = TokenTypes::FUNCTION, short prec = 0, bool left = true);

		// constructor for binary functions
		Func(BinaryFuncEval eval, TokenTypes type = TokenTypes::FUNCTION, short prec = 0, bool left = true);

		double eval(double x, double y = 0);

		UnaryFuncEval u_eval;	// unary function evaluation callback
		BinaryFuncEval b_eval;	// binary function evaluation callback

		TokenTypes type;		// type of function (ie function or operator)
		short prec;				// precedence
		bool left;				// is left associative
		bool unary;				// is a unary function

	private:
		Func(TokenTypes type, short prec, bool left, bool unary);
	};

	/*
		Reference
	*/

	// unary functions
	

	/*
		Node class definitions
	*/

	// base node class
	class Node {
	public:
		Node(std::string name, bool isFunc);

		double eval(double x = 0, double y = 0);

		std::string name;
		bool isFunc;

		Node* right;
		Node* left;
	};

	// function node class
	class FuncNode : public Node {
	public:
		FuncNode(std::string name);

		// set type of function and then assign callback
		void setUnary(bool isUnary);

		// evaluate
		double eval(double x, double y = 0);

		bool isUnary;
		Func func;
	};

	// number node class
	class NumNode : public Node {
	public:
		NumNode(std::string name);

		// return numerical value
		double eval(double x = 0, double y = 0);
	};

	/*
		Main functions
	*/

	// parse infix notation into reverse polish notation (Shunting Yard)
	RPN reversePolishNotation(const char* eqn);

	// parse RPN to tree
	Node* parse(RPN rpn);

	// evaluate tree
	double eval(Node* tree, float x, float y);

	/*
		Utility function definitions
	*/

	// determine if vector contains values
	template<typename T>
	bool contains(std::vector<T> v, T x);

	// obtain key list
	template<typename T>
	inline std::vector<std::string> keys(std::map<std::string, T> m);

	// obtain combined key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m1, std::map<std::string, T> m2);

	// determine if character is number
	bool isNumber(char c, bool acceptDecimal, bool acceptNegative);

	// determine if entire string is number
	bool isNumber(const char* str);

	// determine if string only contains numerical characters
	bool containsNumbers(const char* str);

	// get numerical value of string
	double getNumericalVal(const char* str, float x, float y);

	// determine if string matches a function
	bool isFunction(std::string str);

	// determine if function is left associative
	bool isLeftAssociative(std::string str);

	// get function precedence
	short getPrecedence(std::string str);

	// find element from list in the equation starting at index i
	std::string findElement(int i, const char* eqn, std::vector<std::string> list);
}

#endif