#pragma once

#include "Rule.h"
#include "Predicate.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

class datalogProgram {
public:
	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Rule> rules;
	vector<Predicate> queries;
	set<string> domain;

	void toString() {
		cout << "Success!" << endl;

		cout << "Schemes(" << schemes.size() << "):" << endl;
		for (unsigned int i = 0; i < schemes.size(); i++) {
			cout << " " << schemes[i].toString() << endl;
		}

		cout << "Facts(" << facts.size() << "):" << endl;
		for (unsigned int i = 0; i < facts.size(); i++) {
			cout << " " << facts[i].toString() << "." << endl;
		}

		cout << "Rules(" << rules.size() << "):" << endl;
		for (unsigned int i = 0; i < rules.size(); i++) {
			cout << " " << rules[i].toString() << "." << endl;
		}

		cout << "Queries(" << queries.size() << "):" << endl;
		for (unsigned int i = 0; i < queries.size(); i++) {
			cout << " " << queries[i].toString() << "?" << endl;
		}

		cout << "Domain(" << domain.size() << "):" << endl;

		set<string>::iterator t = domain.begin();
		for (unsigned int i = 0; i < domain.size(); i++) {
			cout << " " << *t << endl;
			t++;
		}
	}

	void addScheme(Predicate tempPred) { schemes.push_back(tempPred); }
	void addFact(Predicate tempPred) { facts.push_back(tempPred); }
	void addRule(Rule tempRule) { rules.push_back(tempRule); }
	void addQuery(Predicate tempPred) { queries.push_back(tempPred); }
	void addDomain(string tempString) { domain.insert(tempString); }
	vector<Predicate> getQueries() { return queries; }
	set<string> getDomain() { return domain; }
};