#include "Lexer.h"

//Missing parts of the domain. It's a set, so sets don't have duplicates. 
//Anytime you pushback a paramater back into the fact vector, do an insert into your set.
		//Right after predicate pushback.

void Lexer::scan(string input) {
	//cout << "Scan activated." << endl;
	lineNumber = 1;
	tokenNumber = 0;
	inputFile.open(input.c_str());
	temp = inputFile.get();
	int loopNum = 0;

	while (inputFile.is_open()) {
		//cout << "Lexer scan loop " << loopNum << " has begun." << endl;
		if (isspace(temp)) {
			if (temp == '\n') {
				lineNumber++;
			}
			temp = inputFile.get();
		}
		else {
			switch (temp) {
			case ',':
				//cout << "Checking comma." << endl;
				addComma();
				temp = inputFile.get();
				break;
			case '.':
				//cout << "Checking period." << endl;
				addPeriod();
				temp = inputFile.get();
				break;
			case '?':
				//cout << "Checking Q_Mark." << endl;
				addQMark();
				temp = inputFile.get();
				break;
			case '(':
				//cout << "Checking left paren." << endl;
				addLeftParen();
				temp = inputFile.get();
				break;
			case ')':
				//cout << "Checking right paren." << endl;
				addRightParen();
				temp = inputFile.get();
				break;
			case ':':
				//cout << "Checking colon." << endl;
				isColonDash();
				temp = inputFile.get();
				break;
			case '*':
				//cout << "Checking multiply." << endl;
				addMultiply();
				temp = inputFile.get();
				break;
			case '+':
				//cout << "Checking plus." << endl;
				addPlus();
				temp = inputFile.get();
				break;
			case '#':
				//cout << "Checking comment." << endl;
				isComment();
				break;
			case '\'':
				//cout << "Checking string." << endl;
				getString();
				//cout << "String is finished." << endl;
				break;
			case EOF:
				//cout << "Checking EOF." << endl;
				addEOF();
				//cout << "EOF has been added." << endl;
				temp = inputFile.get();
				return;
			default:
				if (isalpha(temp)) {
					//cout << "Checking ID." << endl;
					isID(getID());
				}
				else {
					string tempString;
					tempString += temp;
					//cout << "Checking undefined." << endl;
					addUndefined(tempString, lineNumber);
					temp = inputFile.get();
				}
			}
		}
		loopNum++;
	}
}

string Lexer::getID() {
	string tempString = "";
	temp = inputFile.get();
	cout << temp << endl;
	while (isalnum(temp)) {
		tempString += temp;
		temp = inputFile.get();
	}
	return tempString;
}

void Lexer::isComment() {
	int startLine = lineNumber;
	if (inputFile.peek() == '|') {
		temp = inputFile.get();
		string input = "#|";

		while (temp + inputFile.peek() != ('|' + '#')) {		//Changed from (1) to (temp + inputFile.peek() != ('|' + '#'))
			if (temp == '|') {
				if (inputFile.peek() == '#') {
					break;
				}
			}

			if (isNewLine(temp)) {
				lineNumber++;
			}

			if (temp == EOF) {
				addUndefined(input, startLine);
				return;
			}

			input += temp;
			temp = inputFile.get();
		}

		input += "|#";
		temp = inputFile.get();
		//addComment(input, startLine);
	}

	else {
		string input;
		while (!isNewLine(temp) && temp != EOF) {
			input += temp;
			temp = inputFile.get();
		}

		lineNumber++;
		//addComment(input, startLine);
	}

	temp = inputFile.get();
}

void Lexer::getString() {
	int startLine = lineNumber;
	string input = "\'";
	bool done = false;
	int loopNum = 0;

	while (!done) {
		temp = inputFile.get();
		/*cout << "String loop " << loopNum << " has begun." << endl;
		cout << "The variable \"Temp\" is currently " << temp << endl;
		cout << "The variable \"Input\" is currently " << input << endl;*/
		if (temp == '\'' && inputFile.peek() == '\'') {
			//cout << "Empty string detected." << endl;
			input += temp;
			temp = inputFile.get();
			input += temp;
			temp = inputFile.get();
		}

		else if (temp == '\'') {
			done = true;
		}

		else if (temp == EOF) {
			inputFile.unget();
			done = true;
			addUndefined(input, startLine);
			return;
		}

		else if (isNewLine(temp)) {
			lineNumber++;
			input += temp;
			temp = inputFile.get();
		}

		else {
			input += temp;
			/*if (isNewLine(temp)) {
				cout << "New line detected." << endl;
				lineNumber++;
				input += temp;
				temp = inputFile.get();
			}*/
		}
		loopNum++;
	}

	input += '\'';
	addString(input, startLine);
	temp = inputFile.get();
}

void Lexer::isID(string tempString) {
	if (tempString == "Schemes") {
		addSchemes();
	}
	else if (tempString == "Facts") {
		addFacts();
	}
	else if (tempString == "Rules") {
		addRules();
	}
	else if (tempString == "Queries") {
		addQueries();
	}
	else {
		addID(tempString);
	}
}

void Lexer::isColonDash() {
	if (inputFile.peek() == '-') {
		addColonDash();
		temp = inputFile.get();
	}
	else {
		addColon();
	}
}

bool Lexer::isNewLine(char input) {
	if (input == '\n') {
		return true;
	}
	else {
		return false;
	}
}

void Lexer::addComma() {
	Token tempToken;
	tempToken.setType("COMMA");
	tempToken.setValue(",");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addPeriod() {
	Token tempToken;
	tempToken.setType("PERIOD");
	tempToken.setValue(".");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addQMark() {
	Token tempToken;
	tempToken.setType("Q_MARK");
	tempToken.setValue("?");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addLeftParen() {
	Token tempToken;
	tempToken.setType("LEFT_PAREN");
	tempToken.setValue("(");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addRightParen() {
	Token tempToken;
	tempToken.setType("RIGHT_PAREN");
	tempToken.setValue(")");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addColon() {
	Token tempToken;
	tempToken.setType("COLON");
	tempToken.setValue(":");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addColonDash() {
	Token tempToken;
	tempToken.setType("COLON_DASH");
	tempToken.setValue(":-");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addMultiply() {
	Token tempToken;
	tempToken.setType("MULTIPLY");
	tempToken.setValue("*");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addPlus() {
	Token tempToken;
	tempToken.setType("ADD");
	tempToken.setValue("+");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addSchemes() {
	Token tempToken;
	tempToken.setType("SCHEMES");
	tempToken.setValue("Schemes");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addRules() {
	Token tempToken;
	tempToken.setType("RULES");
	tempToken.setValue("Rules");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addQueries() {
	Token tempToken;
	tempToken.setType("QUERIES");
	tempToken.setValue("Queries");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addID(string input) {
	Token tempToken;
	string inputString = input;
	tempToken.setType("ID");
	tempToken.setValue(inputString);
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addFacts() {
	Token tempToken;
	tempToken.setType("FACTS");
	tempToken.setValue("Facts");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addString(string input, int number) {
	Token tempToken;
	string inputString = input;
	tempToken.setType("STRING");
	tempToken.setValue(inputString);
	tempToken.setLine(number);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addComment(string input, int number) {
	Token tempToken;
	string inputString = input;
	tempToken.setType("COMMENT");
	tempToken.setValue(inputString);
	tempToken.setLine(number);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addUndefined(string input, int number) {
	Token tempToken;
	string inputString = input;
	tempToken.setType("UNDEFINED");
	tempToken.setValue(inputString);
	tempToken.setLine(number);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::addEOF() {
	//cout << "This is the addEOF function." << endl;
	Token tempToken;
	tempToken.setType("EOF");
	tempToken.setValue("");
	tempToken.setLine(lineNumber);
	tokens.push_back(tempToken);
	tokenNumber++;
}

void Lexer::print() {
	for (unsigned int i = 0; i < tokens.size(); i++) {
		cout << "(" << tokens[i].getType() << "," << tokens[i].getValue() << "," << tokens[i].getLine() << ")" << endl;
	}
	cout << "Total Tokens = " << tokenNumber << endl;
}

void Lexer::run(std::string input) {
	lineNumber = 1;
	tokenNumber = 0;
	inputFile.open(input);
	temp = inputFile.get();

	while (inputFile.is_open()) {
		if (temp == '\n') {
			lineNumber++;
			temp = inputFile.get();
		}
		else {
			switch (temp) {
			case ',':
				addComma();
				temp = inputFile.get();
				break;
			case '.':
				addPeriod();
				temp = inputFile.get();
				break;
			case '?':
				addQMark();
				temp = inputFile.get();
				break;
			case '(':
				addLeftParen();
				temp = inputFile.get();
				break;
			case ')':
				addRightParen();
				temp = inputFile.get();
				break;
			case ':':
				addColonDash();
				temp = inputFile.get();
				break;
			case '*':
				addMultiply();
				temp = inputFile.get();
				break;
			case '+':
				addPlus();
				temp = inputFile.get();
				break;
			case '#':
				isComment();
				break;
			case '\'':
				getString();
				temp = inputFile.get();
				break;
			case EOF:
				addEOF();
				inputFile.close();
				break;
			default:
				if (isalpha(temp)) {
					isID(getID());
				}
				else {
					string tempString;
					tempString += temp;
					addUndefined(tempString, lineNumber);
					temp = inputFile.get();
				}
			}
		}
	}
}
