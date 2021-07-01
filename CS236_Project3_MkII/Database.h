#pragma once

#include "Relation.h"
#include "Predicate.h"
#include <map>
#include <string>
using namespace std;

class Database {
public:

	map<string, Relation> dMap;

	void addRelation(Relation rel) {
		dMap.insert(pair<string, Relation>(rel.getName(), rel));
	}
	void addValue(string name, vector<string> values) {
		dMap[name].addValue(values);
	}
	map<string, Relation> getDatabase() {
		return dMap;
	}
	bool has(string input) {
		if (dMap.find(input) != dMap.end()) {
			return true;
		}
		else {
			return false;
		}
	}
};

