#pragma once

#include <set>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

class Relation {
public:
	string name;
	vector<string> schema;
	set<vector<string>> values;

	void setName(string input) { name = input; }
	void setAttribute(int num, string input) { schema[num] = input; }
	void setSchema(vector<string> input) { schema = input; }
	void setValues(set<vector<string>> input) { values = input; }
	void addSchema(string input) { schema.push_back(input); }
	void addValue(vector<string> input) { values.insert(input); }
	void clear();
	string getName() { return name; }
	vector<string> getSchema() { return schema; }
	set<vector<string>> getValues() { return values; }

	Relation select(int, string);
	Relation selectDupe(vector<pair<string, vector<int>>>);
	Relation project(vector<pair<string, vector<int>>>);
	Relation rename(vector<int>, string);
	void toString();
	bool goodTuple(vector<pair<string, vector<int>>>, vector<string>, int);
};

#pragma once
