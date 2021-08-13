#include<iostream>
#include<stack>
#include<string>
#include<algorithm>

int getPriority(char op) {
	switch (op) {
	case '+': return 1;
	case '-': return 1; 
	case '*': return 2;
	case '/': return 2;
	case '^': return 3;
	default: return -1;
	}
}

bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isLetter(char c) {
	return c >= 'a' && c <= 'z';
}

std::string infixToPostfix(const std::string& expression) {
	std::string result = "";
	std::stack<char> ops;

	for (size_t i = 0; i < expression.size(); i++) {
		char c = expression[i];
		if (isLetter(c)) {
			result += c;
		}
		else if (c == '(') {
			ops.push(c);
		}
		else if (c == ')') {
			while (!ops.empty() && ops.top() != '(') {
				result += ops.top();
				ops.pop();
			}
			ops.pop();
		}
		else if (isOperator(c)) {
			while (!ops.empty() && getPriority(c) <= getPriority(ops.top())) {
				result += ops.top();
				ops.pop();
			}
			ops.push(expression[i]);
		}
		else { //whitespace
			continue;
		}
	}

	while (!ops.empty()) {
		result += ops.top();
		ops.pop();
	}

	return result;
}


std::string modifiedInfixToPstfix(const std::string& expression) {
	std::string postfix = "";
	std::stack<char> ops;

	for (size_t i = 0; i < expression.size(); i++) {
		char c = expression[i];
		if (isLetter(c)) {
			postfix += c;
		}
		else if (c == '(') {
			ops.push(c);
		}
		else if (c == ')') {
			while (!ops.empty() && ops.top() != '(') {
				postfix += ops.top();
				ops.pop();
			}
			ops.pop();
		}
		else if (isOperator(c)) {
			if (c == '^') {
				while (!ops.empty() && getPriority(c) <= getPriority(ops.top())) { // here we use <=
					postfix += ops.top();
					ops.pop();
				}
			}
			else {
				while (!ops.empty() && getPriority(c) < getPriority(ops.top())) { // only <
					postfix += ops.top();
					ops.pop();
				}
			}

			ops.push(c);
		}
		else { // whitespace
			continue;
		}
	}

	while (!ops.empty()) {
		postfix += ops.top();
		ops.pop();
	}

	return postfix;
}
std::string infixToPrefix(std::string& expression) {

	std::reverse(expression.begin(), expression.end());

	for (size_t i = 0; i < expression.size(); i++) {
		if (expression[i] == '(') {
			expression[i] = ')';
		}
		else if (expression[i] == ')') {
			expression[i] = '(';
		}
	}

	std::string prefix = modifiedInfixToPstfix(expression);
	std::reverse(prefix.begin(), prefix.end());

	return prefix;
}

std::string prefixToInfix(const std::string& expression) {
	std::stack<std::string> st;

	for (int i = expression.size() - 1; i >= 0; i--) {
		char c = expression[i];
		if (isLetter(c)) {
			st.push(std::string(1, c));
		}
		else if (isOperator(c)) {
			//st cannot contain less than two elements, 
			//because we read a valid prefix expression in reverse order
			//and when me meet operator
			//we must have already read two operands

			std::string operand1 = st.top();
			st.pop();
			std::string operand2 = st.top();
			st.pop();

			std::string newOperand = '(' + operand1 + c + operand2 + ')';
			st.push(newOperand);
		}
		else { // whitespace
			continue;
		}
	}

	return st.top();
}

std::string prefixToPostfix(const std::string& expression) {
	std::stack<std::string> st;

	for (int i = expression.size(); i >= 0; i--) {
		char c = expression[i];
		if (isLetter(c)) {
			st.push(std::string(1, c));
		}
		else if (isOperator(c)) {
			std::string operand1 = st.top();
			st.pop();
			std::string operand2 = st.top();
			st.pop();

			std::string newOperand = operand1 + operand2 + c;
			st.push(newOperand);
		}
		else { //whitespace
			continue;
		}
	}

	return st.top();
}

//==========   Tests   ==========

void testInfixToPostfix() {
	std::cout << "InfixToPostfix tests:\n";

	std::string infix1 = "a+b*c";
	std::string infix2 = "a+b/c-d+b*f/h";
	std::string infix3 = "a+b*(c^d-e)^( f+g*h)-i";
	std::string infix4 = "a+b+c+d * e";
	std::string infix5 = "u+w/z*y+x";

	std::cout << infixToPostfix(infix1) << std::endl;
	std::cout << infixToPostfix(infix2) << std::endl;
	std::cout << infixToPostfix(infix3) << std::endl;
	std::cout << infixToPostfix(infix4) << std::endl;
	std::cout << infixToPostfix(infix5) << std::endl;

}

void testInfixToPrefix() {
	std::cout << "\nInfixToPrefix tests:\n";

	std::string infix1 = "x + y * z / w + u";
	std::string infix2 = "a+b+c+d";
	std::string infix3 = "a*b + c*d     +a^b^c +h";

	std::cout << infixToPrefix(infix1) << std::endl;
	std::cout << infixToPrefix(infix2) << std::endl;
	std::cout << infixToPrefix(infix3) << std::endl;
}

void testPrefixToInfix() {
	std::cout << "\nPrefixToInfix tests:\n";

	std::string prefix1 = "+++abcd";
	std::string prefix2 = "+ + +*ab *cd    ^a^bch";
	std::string prefix3 = "*+ab-cd";
	std::string prefix4 = "*-x/yz-/xuv";

	std::cout << prefixToInfix(prefix1) << std::endl;
	std::cout << prefixToInfix(prefix2) << std::endl;
	std::cout << prefixToInfix(prefix3) << std::endl;
	std::cout << prefixToInfix(prefix4) << std::endl;
}

void testPrefixToPostfix() {
	std::cout << "\nPrefixToPostfix tests:\n";

	std::string prefix1 = "+++abcd";
	std::string prefix2 = "+ + +*ab *cd    ^a^bch";
	std::string prefix3 = "*+ab-cd";
	std::string prefix4 = "*-x/yz-/xuv";

	std::cout << prefixToPostfix(prefix1) << std::endl;
	std::cout << prefixToPostfix(prefix2) << std::endl;
	std::cout << prefixToPostfix(prefix3) << std::endl;
	std::cout << prefixToPostfix(prefix4) << std::endl;
}

int main() {
	testInfixToPostfix();
	testInfixToPrefix();
	testPrefixToInfix();
	testPrefixToPostfix();
	return 0;
}