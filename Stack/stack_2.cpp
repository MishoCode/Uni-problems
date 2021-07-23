#include<iostream>
#include<stack>
#include<string>
#include<cassert>

const std::string OPEN_BRACKET_TYPES = "([{";
const std::string CLOSE_BRACKET_TYPES = ")]}";

bool isOpenBracket(char c) {
	return 0 <= (int)OPEN_BRACKET_TYPES.find(c);
}

bool isClosedBracket(char c) {
	return 0 <= (int)CLOSE_BRACKET_TYPES.find(c);
}

bool isMatchingBracket(char openedBracket, char closedBracket) {
	int bracketIndex = OPEN_BRACKET_TYPES.find(openedBracket);
	assert(bracketIndex >= 0 && bracketIndex <= 2);
	return closedBracket == CLOSE_BRACKET_TYPES[bracketIndex];
}

bool hasValidBrackets(const std::string& str) {
	std::stack<char> openedBrackets;

	for (char c : str) {
		if (isOpenBracket(c)) {
			openedBrackets.push(c);
		}
		else if(isClosedBracket(c)){
			if (!openedBrackets.empty() && isMatchingBracket(openedBrackets.top(),c)) {
				openedBrackets.pop();
			}
			else {
				return false;
			}
		}
	}

	return openedBrackets.empty();
}

bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool hasRedundantBrackets(const std::string& validMathExpr) {
	std::stack<char> s;
	for (char c : validMathExpr) {
		if (c == ')') {
			char current = s.top();
			s.pop();

			bool operatorFound = false;
			while (!s.empty() && current != '(') {
				if (isOperator(current)) {
					operatorFound = true;
				}
				current = s.top();
				s.pop();
			}

			if (!operatorFound) {
				return true;
			}
		}
		else {
			s.push(c);
		}
	}

	return false;
}

void testHasValidBrackets() {
	std::cout << hasValidBrackets("( ala bala)")<<std::endl;// 1
	std::cout << hasValidBrackets("([]   )")<< std::endl;// 1
	std::cout << hasValidBrackets("([]  } )")<<std::endl;//0
	std::cout << hasValidBrackets("([]  { ( [])} )")<<std::endl;//;1
	std::cout << hasValidBrackets("([] ]] 678)")<<std::endl;//0
	std::cout << hasValidBrackets("]")<<std::endl;//0
	std::cout << hasValidBrackets("(")<<std::endl;//0
	std::cout << hasValidBrackets("( aaa [bbbbb{}b] () () [({hello world!})]  )")<<std::endl;//1
}

void testHasRedundantBrackets() {
	std::cout << hasRedundantBrackets("((1+2))") << std::endl;//1
	std::cout << hasRedundantBrackets("(1+2)") << std::endl;//0
	std::cout << hasRedundantBrackets("(3*(1+2)-(5/6))") << std::endl;//0
	std::cout << hasRedundantBrackets("1+(1)") << std::endl;//1
	std::cout << hasRedundantBrackets("1+2=3") << std::endl;//0
}
int main() {
	std::cout << "Test hasValidBrackets: " << std::endl;
	testHasValidBrackets();

	std::cout << std::endl;

	std::cout << "Test hasRedundantBrackets: " << std::endl;
	testHasRedundantBrackets();
	return 0;
}