#pragma once

#include "Lexer.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Expression.h"
#include "Token.h"
#include <string>
#include <vector>
using namespace std;

class Parser {
public:
	int vectorPoint;
	int leftParen;
	int rightParen;
	datalogProgram program;
	vector<Parameter> params;
	Predicate newPredicate;
	Rule newRule;
	Expression newExpression;
	vector<Token> tokens;

	vector<Predicate> getQueries() { return program.getQueries(); }
	set<string> getDomain() { return program.getDomain(); }

	bool parse(vector<Token> tempTokens) {
		try {
			tokens = tempTokens;
			vectorPoint = 0;
			leftParen = 0;
			rightParen = 0;
			match("SCHEMES");
			match("COLON");
			scheme();
			schemelist();
			match("FACTS");
			match("COLON");
			if (tokens[vectorPoint].getType() != "RULES") {
				factList();
			}
			match("RULES");
			match("COLON");
			if (tokens[vectorPoint].getType() != "QUERIES") {
				ruleList();
			}
			match("QUERIES");
			match("COLON");
			toQuery();
			toQueryList();
			program.toString();
		}
		catch (Token newToken) {
			cout << "Failure!" << endl << "  ";
			newToken.printToken();
			return false;
		}
		return true;
	}

	void makeExpression() {
		if (leftParen == rightParen) {
			newPredicate.addParam(newExpression.getExpression());
			newExpression.clearExpression();
			leftParen = 0;
			rightParen = 0;
		}
	}

	void match(string input) {
		if (input == tokens[vectorPoint].getType()) { //Need to ignore comments. Could delete?			
			vectorPoint++;
		}
		else {
			throw(tokens[vectorPoint]);
		}
	}

	void scheme() {
		newPredicate.setName(tokens[vectorPoint].getValue());
		match("ID");
		match("LEFT_PAREN");
		newPredicate.addParam(tokens[vectorPoint].getValue());
		match("ID");
		if (tokens[vectorPoint].getType() == "COMMA") {
			idList();
		}
		match("RIGHT_PAREN");
		program.addScheme(newPredicate);
		newPredicate.params.clear();
	}

	void schemelist() {
		while (tokens[vectorPoint].getType() != "FACTS") {
			scheme();
		}
	}

	void idList() {
		match("COMMA");
		newPredicate.addParam(tokens[vectorPoint].getValue());
		match("ID");
		if (tokens[vectorPoint].getType() == "COMMA") {
			idList();
		}
	}

	void factList() {
		fact();
		while (tokens[vectorPoint].getType() != "RULES") {
			factList();
		}
	}

	void fact() {
		newPredicate.setName(tokens[vectorPoint].getValue());
		match("ID");
		match("LEFT_PAREN");
		newPredicate.addParam(tokens[vectorPoint].getValue());
		program.addDomain(tokens[vectorPoint].getValue());
		match("STRING");
		if (tokens[vectorPoint].getType() == "COMMA") {
			stringList();
		}
		match("RIGHT_PAREN");
		match("PERIOD");
		program.addFact(newPredicate);
		newPredicate.params.clear();
	}

	void stringList() {
		match("COMMA");
		newPredicate.addParam(tokens[vectorPoint].getValue());
		program.addDomain(tokens[vectorPoint].getValue());
		match("STRING");
		if (tokens[vectorPoint].getType() == "COMMA") {
			stringList();
		}
	}

	void ruleList() {
		rule();
		program.addRule(newRule);
		newRule.predicates.clear();
		while (tokens[vectorPoint].getType() != "QUERIES") {
			ruleList();
		}
	}

	void rule() {
		headPredicate();
		match("COLON_DASH");
		predicate();
		newRule.addPred(newPredicate);
		newPredicate.params.clear();
		if (tokens[vectorPoint].getType() == "COMMA") {
			predicateList();
		}
		match("PERIOD");
	}

	void headPredicate() {
		newPredicate.setName(tokens[vectorPoint].getValue());
		match("ID");
		match("LEFT_PAREN");
		newPredicate.addParam(tokens[vectorPoint].getValue());
		match("ID");
		if (tokens[vectorPoint].getType() == "COMMA") {
			idList();
		}
		match("RIGHT_PAREN");
		newRule.setHeadPred(newPredicate);
		newPredicate.params.clear();
	}

	void predicate() {
		newPredicate.setName(tokens[vectorPoint].getValue());
		match("ID");
		match("LEFT_PAREN");
		parameter();
		if (tokens[vectorPoint].getType() == "COMMA") {
			paramList();
		}
		match("RIGHT_PAREN");
	}

	void parameter() {
		if (tokens[vectorPoint].getType() == "STRING") {
			if (leftParen != rightParen) {
				newExpression.addExpression(tokens[vectorPoint].getValue());
			}
			else {
				newPredicate.addParam(tokens[vectorPoint].getValue());
			}
			match("STRING");
		}
		else if (tokens[vectorPoint].getType() == "ID") {
			if (leftParen != rightParen) {
				newExpression.addExpression(tokens[vectorPoint].getValue());
			}
			else {
				newPredicate.addParam(tokens[vectorPoint].getValue());
			}
			match("ID");
		}
		else {
			expression();
			makeExpression();
		}
	}

	void expression() {
		leftParen++;
		newExpression.addExpression(tokens[vectorPoint].getValue());
		match("LEFT_PAREN");
		parameter();
		operate();
		parameter();
		newExpression.addExpression(tokens[vectorPoint].getValue());
		match("RIGHT_PAREN");
		rightParen++;
	}

	void operate() {
		if (tokens[vectorPoint].getType() == "ADD") {
			newExpression.addExpression(tokens[vectorPoint].getValue());
			match("ADD");
		}
		else if (tokens[vectorPoint].getType() == "MULTIPLY") {
			newExpression.addExpression(tokens[vectorPoint].getValue());
			match("MULTIPLY");
		}
		else {
			throw(tokens[vectorPoint]);
		}
	}

	void paramList() {
		match("COMMA");
		parameter();
		if (tokens[vectorPoint].getType() == "COMMA") {
			paramList();
		}
	}

	void predicateList() {
		match("COMMA");
		predicate();
		newRule.addPred(newPredicate);
		newPredicate.params.clear();
		if (tokens[vectorPoint].getType() == "COMMA") {
			predicateList();
		}
	}

	void toQuery() {
		predicate();
		match("Q_MARK");
		program.addQuery(newPredicate);
		newPredicate.params.clear();
	}

	void toQueryList() {
		while (tokens[vectorPoint].getType() != "EOF") {
			toQuery();
		}
	}


};