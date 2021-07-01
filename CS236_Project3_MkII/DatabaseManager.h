#pragma once

#include "Parser.h"
#include "Relation.h"
#include "Predicate.h"
#include "Database.h"
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <utility>
using namespace std;

class DatabaseManager {
public:
	Database db;
	Predicate query;
	vector<pair<string, vector<int>>> IDs;

	void manage(Database, vector<Predicate>, set<string>);
	Relation getRelation(string, Predicate, set<string>);
	void addID(string, int);
	void getID(string, int);
};