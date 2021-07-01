#pragma once

#include "Predicate.h"

class Rule {
public:
	Predicate headPred;
	vector<Predicate> predicates;

	void addPred(Predicate tempPred) { predicates.push_back(tempPred); }
	void setHeadPred(Predicate tempPred) { headPred = tempPred; }
	string toString() {
		string output;

		output += headPred.toString();
		output += " :- ";

		for (unsigned int i = 0; i < predicates.size(); i++) {
			output += predicates[i].toString();

			if (i + 1 < predicates.size()) {
				output += ",";
			}
		}
		return output;
	}
};