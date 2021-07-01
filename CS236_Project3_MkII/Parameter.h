#pragma once

#include <string>
#include <sstream>
using namespace std;

class Parameter {

public:
	string param;
	void setParam(string input) { param = input; }
	string toString() { return param; }
	string getParam() {
		string output;
		output = param;
		return output;
	}
};