#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
using namespace std;

class Token {
private:
	std::string tokenType;
	std::string tokenValue;
	int lineNumber;

public:
	void setType(std::string input) { tokenType = input; }
	void setValue(std::string input) { tokenValue = input; }
	void setLine(int input) { lineNumber = input; }
	std::string getType() { return tokenType; }
	std::string getValue() { return tokenValue; }
	int getLine() { return lineNumber; }
	void printToken() {
		cout << "(" << tokenType << ",\"" << tokenValue << "\"," << lineNumber << ")" << endl;
	}


};

#endif //TOKEN_H