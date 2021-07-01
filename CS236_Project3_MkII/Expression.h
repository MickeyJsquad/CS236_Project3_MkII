#pragma once

#include <string>
using namespace std;

class Expression {
public:
	string exp;

	void addExpression(string newExp) { exp = newExp; }
	string getExpression() { return exp; }
	void clearExpression() { exp = ""; }
};