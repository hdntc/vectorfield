#include "ShuntingYard.hpp"
#include <iostream>

namespace ShuntingYard {
	std::map<std::string, Func> unary_functions = {
		{ "sin", Func(std::sin) }
	};
	// binary functions
	std::map<std::string, Func> binary_functions = {
		{ "+", Func([](double x, double y) -> double { return x + y; }, TokenTypes::OPERATOR, 2) },
		{ "-", Func([](double x, double y) -> double { return x - y; }, TokenTypes::OPERATOR, 2) },
		{ "*", Func([](double x, double y) -> double { return x * y; }, TokenTypes::OPERATOR, 3) },
		{ "/", Func([](double x, double y) -> double { return x / y; }, TokenTypes::OPERATOR, 3) },
		{ "^", Func(std::pow, TokenTypes::OPERATOR, 4, false) }
	};

	// function names
	std::vector<std::string> functionNames = keys<Func>(unary_functions, binary_functions);

	// constants
	std::map<std::string, double> constants = {
		{ "pi", std::atan(1) * 4 },
		{ "e", std::exp(1) }
	};

	// constant names
	std::vector<std::string> constantNames = keys<double>(constants);

	// variables
	std::map<std::string, double> variables;

	// operators
	std::vector<char> operators = { '+', '-', '/', '*', '^' };
	// left brackets
	std::vector<char> leftBrackets = { '(', '{', '[' };
	// right brackets
	std::vector<char> rightBrackets = { ')', '}', ']' };

	Func::Func()
		: type(TokenTypes::OPERATOR), prec(0), left(true), unary(true), u_eval(nullptr), b_eval(nullptr) {}

	Func::Func(UnaryFuncEval eval, TokenTypes type, short prec, bool left)
		: Func(type, prec, left, true) {
		u_eval = eval;
	}

	Func::Func(BinaryFuncEval eval, TokenTypes type, short prec, bool left)
		: Func(type, prec, left, false) {
		b_eval = eval;
	}

	double Func::eval(double x, double y) {
		return this->unary ? u_eval(x) : b_eval(x, y);
	}

	Func::Func(TokenTypes type, short prec, bool left, bool unary)
		: type(type), prec(prec), left(left), unary(unary), u_eval(nullptr), b_eval(b_eval) {}

	Node::Node(std::string name, bool isFunc)
		: name(name), isFunc(isFunc) {}

	FuncNode::FuncNode(std::string name)
		: Node(name, true) {}

	void FuncNode::setUnary(bool isUnary) {
		this->isUnary = isUnary;

		this->func = isUnary ? unary_functions[name] : binary_functions[name];
	}

	double FuncNode::eval(double x, double y) {
		return this->func.eval(x, y);
	}

	NumNode::NumNode(std::string name)
		: Node(name, false) {}

	double NumNode::eval(double x, double y) {
		return getNumericalVal(name.c_str(), x, y);
	}

	RPN reversePolishNotation(const char* eqn) {
		std::vector<std::string> queue;
		std::stack<std::string> stack;

		std::string obj = "";
		TokenTypes type = TokenTypes::ELSE;
		TokenTypes prevType = TokenTypes::ELSE; // negative sign detection

		bool acceptDecimal = true;
		bool acceptNegative = true;

		// token reading and detection
		for (int i = 0, eqLen = (int)strlen(eqn); i < eqLen; i++) {
			char t = eqn[i];

			// skip spaces and commas
			if (t == ' ' || t == ',') {
				//prevType = TokenTypes::ELSE;
				continue;
			}

			// classify token
			if (isNumber(t)) {
				type = TokenTypes::CONSTANT;
				if (t == '.') {
					acceptDecimal = false;
				}
				else if (t == '-') {
					acceptNegative = false;
				}

				int startI = i;
				if (i < eqLen - 1) {
					while (isNumber(eqn[i + 1], acceptDecimal, acceptNegative)) {
						i++;
						if (i >= eqLen - 1) {
							break;
						}
					}
				}
				obj = std::string(eqn).substr(startI, i - startI + 1);

				// subtraction sign detection
				if (obj == "-") {
					type = TokenTypes::OPERATOR;
				}
			}
			else {
				obj = findElement(i, eqn, functionNames);
				if (obj != "") {
					// found valid object
					type = contains<char>(operators, obj[0]) ? TokenTypes::OPERATOR : TokenTypes::FUNCTION;
				}
				else {
					obj = findElement(i, eqn, constantNames);
					if (obj != "") {
						// found valid object
						type = TokenTypes::CONSTANT;
					}
					else {
						obj = findElement(i, eqn, {"x", "y"});
						if (obj != "") {
							type = TokenTypes::CONSTANT;
						}
						else if (contains<char>(leftBrackets, t)) {
							type = TokenTypes::LPAREN;
							obj = "(";
						}
						else if (contains<char>(rightBrackets, t)) {
							type = TokenTypes::RPAREN;
							obj = ")";
						}
						else {
							type = TokenTypes::ELSE;
						}
					}
				}
				i += obj.size() - 1;
			}

			// do something with the token
			const char* last_stack = (stack.size() > 0) ? stack.top().c_str() : "";
			switch (type) {
			case TokenTypes::CONSTANT:
				queue.push_back(obj);
				break;
			case TokenTypes::FUNCTION:
				stack.push(obj);
				break;
			case TokenTypes::OPERATOR:
				if (stack.size() != 0) {
					while (
						/*
							stk = stack top = last_stack
							obj = obj

										stk is a function
									AND
										stk is not an operator
								OR
									stk has a higher precedence than obj
								OR
										they have equal precedence
									AND
										stk is left associative
							AND
								stk is not a left bracket
						*/
						(
							(contains<std::string>(functionNames, last_stack) &&
								!contains<char>(operators, last_stack[0])) ||
							getPrecedence(last_stack) > getPrecedence(obj) ||
							((getPrecedence(last_stack) == getPrecedence(obj)) &&
								isLeftAssociative(last_stack))
							) &&
						!contains<char>(leftBrackets, last_stack[0])
						) {
						// pop from the stack to the queue
						queue.push_back(stack.top());
						stack.pop();
						if (stack.size() == 0) {
							break;
						}
						last_stack = stack.top().c_str();
					}
				}
				stack.push(obj);
				break;
			case TokenTypes::LPAREN:
				stack.push(obj);
				break;
			case TokenTypes::RPAREN:
				while (last_stack[0] != '(') {
					// pop from the stack to the queue
					queue.push_back(stack.top());
					stack.pop();
					last_stack = stack.top().c_str();
				}
				stack.pop();
				break;
			default:
				return queue;
			}

			// reset type
			prevType = type;
		}

		while (stack.size() > 0) {
			// pop from the stack to the queue
			queue.push_back(stack.top());
			stack.pop();
		}

		return queue;
	}

	// parse RPN to tree
	Node* parse(RPN rpn) {
		std::stack<Node*> stack;

		for (std::string item : rpn) {
			if (isNumber(item.c_str())) {
				// push number node
				stack.push(new NumNode(item));
			}
			else {
				// function
				FuncNode* f = new FuncNode(item);
				if (contains<std::string>(keys(binary_functions), item)) {
					f->setUnary(false);
					// set children of node

					// right child is second argument
					f->right = stack.top();
					stack.pop();

					// left child is first argument
					f->left = stack.top();
					stack.pop();
				}
				else if (contains<std::string>(keys(unary_functions), item)) {
					f->setUnary(true);
					// set child of node
					f->left = stack.top();
					stack.pop();
				}
				stack.push(f);
			}
		}

		if (stack.size() == 0) {
			return nullptr;
		}

		return stack.top();
	}

	// evaluate tree
	double eval(Node* tree, float x, float y) {
		if (tree->isFunc) {
			FuncNode* ftree = (FuncNode*)tree;
			if (ftree->isUnary) {
				// evaluate child recursively and then evaluate with return value
				return ftree->eval(eval(tree->left, x, y));
			}
			else {
				// evaluate each child recursively and then evaluate with return value
				return ftree->eval(eval(tree->left, x, y), eval(tree->right, x, y));
			}
		}
		else {
			// number node
			return ((NumNode*)tree)->eval(x, y);
		}
	}

	/*
		Utility function definitions
	*/

	// determine if vector contains values
	template<typename T>
	bool contains(std::vector<T> v, T x) {
		return std::find(v.begin(), v.end(), x) != v.end();
	}

	// obtain key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m) {
		std::vector<std::string> ret;

		// push each key from each pair
		for (auto const& element : m) {
			ret.push_back(element.first);
		}

		return ret;
	}

	// obtain combined key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m1, std::map<std::string, T> m2) {
		// get keys from each map
		std::vector<std::string> keySet1 = keys<T>(m1);
		std::vector<std::string> keySet2 = keys<T>(m2);

		// insert the second list into first
		keySet1.insert(keySet1.end(), keySet2.begin(), keySet2.end());

		// return result
		return keySet1;
	}

	// determine if character is number
	bool isNumber(char c, bool acceptDecimal, bool acceptNegative) {
		// digits
		if (c >= '0' && c <= '9') {
			return true;
		}
		// decimal point
		else if (acceptDecimal && c == '.') {
			return true;
		}
		// negative sign
		else if (acceptNegative && c == '-') {
			return true;
		}

		return false;
	}

	// determine if entire string is number
	bool isNumber(const char* str) {
		// it's a constant, variable, or a numerical string
		return contains<std::string>(constantNames, str) ||
			contains<std::string>({"x", "y"}, str) ||
			containsNumbers(str);
	}

	// determine if string only contains numerical characters
	bool containsNumbers(const char* str) {
		// cannot be a single decimal point or negative sign
		if (std::strcmp(str, ".") == 0 || std::strcmp(str, "-") == 0) {
			return false;
		}

		std::string obj = std::string(str);

		// try to prove wrong
		bool acceptDecimal = true;
		if (isNumber(obj[0], true, true)) {
			// check first character for negative sign
			if (obj[0] == '.') {
				// cannot be any more decimal points
				acceptDecimal = false;
			}
		}
		else {
			return false;
		}

		for (unsigned int i = 1, len = obj.size(); i < len; i++) {
			// do not accept anymore negative signs
			if (!isNumber(obj[i], acceptDecimal, false)) {
				return false;
			}

			if (obj[i] == '.') {
				// cannot be any more decimal points
				acceptDecimal = false;
			}
		}

		return true;
	}

	// get numerical value of string
	double getNumericalVal(const char* str, float x = 0, float y = 0) {
		if (contains<std::string>(constantNames, str)) {
			// is a constant
			return constants[str];
		}
		else if (std::string(str) == "x") {
			return x;
		}
		else if (std::string(str) == "y") { return y; }
		else {
			// is a number
			return std::atof(str);
		}
	}

	// determine if string matches a function
	bool isFunction(std::string str) {
		return contains<std::string>(functionNames, str);
	}

	// determine if function is left associative
	bool isLeftAssociative(std::string str) {
		return binary_functions[str].left;
	}

	// get function precedence
	short getPrecedence(std::string str) {
		if (contains<std::string>(keys(binary_functions), str)) {
			return binary_functions[str].prec;
		}

		// only care about operators, which are binary functions, so otherwise we can return 0
		return 0;
	}

	// find element from list in the equation starting at index i
	std::string findElement(int i, const char* eqn, std::vector<std::string> list) {
		for (std::string item : list) {
			int n = (int)item.size();
			if (std::string(eqn).substr(i, n) == item) {
				return item;
			}
		}

		return "";
	}
}