#pragma once

#include "Parameter.h"
#include <vector>

class Predicate {
public:
	string name;
	vector<Parameter> params;

	void setName(string input) { name = input; }
	void addParam(string input) {
		Parameter newParam;
		newParam.setParam(input);
		params.push_back(newParam);
	}
	string getName() { return name; }
	vector<Parameter> getParams() { return params; }
	string toString() {
		string paramReturn;

		paramReturn += name + "(";

		for (unsigned int i = 0; i < params.size(); i++) {
			paramReturn += params[i].toString();

			if (i + 1 < params.size()) {
				paramReturn += ",";
			}
		}
		paramReturn += ")";
		return paramReturn;
	}
};