#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Lexer : public Token {
private:
	int lineNumber = 0;
	int tokenNumber = 0;
	char temp;
	ifstream inputFile;
	Token addToken;
	vector<Token> tokens;
public:
	void scan(string input);
	void run(std::string input);
	std::string getID();
	void getString();
	void isID(std::string input);
	void isColonDash();
	void isComment();
	bool isNewLine(char input);
	void addComma();
	void addPeriod();
	void addQMark();
	void addLeftParen();
	void addRightParen();
	void addColon();
	void addColonDash();
	void addMultiply();
	void addPlus();
	void addSchemes();
	void addFacts();
	void addRules();
	void addQueries();
	void addID(std::string input);
	void addString(std::string input, int number);
	void addComment(std::string input, int number);
	void addUndefined(std::string input, int number);
	void addEOF();
	void print();
	vector<Token> getVector() { return tokens; }
};


#endif //LEXER_H