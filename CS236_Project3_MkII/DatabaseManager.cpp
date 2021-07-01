#pragma once

#include "DatabaseManager.h"

void DatabaseManager::manage(Database db, vector<Predicate> queries, set<string> domain) {
	this->db = db;
	for (unsigned int i = 0; i < queries.size(); i++) {
		IDs.clear();
		query = queries[i];
		cout << query.toString() << "?";
		Relation newRel = getRelation(query.getName(), query, domain);
		if (newRel.getValues().size() != 0) {
			cout << "Yes(" << newRel.getValues().size() << ")" << endl;
			newRel.toString();
		}
		else {
			cout << "No." << endl;
		}
	}
}

Relation DatabaseManager::getRelation(string name, Predicate pred, set<string> domain) {
	Relation newRel;
	newRel.setName(query.getName());
	newRel.setSchema(db.getDatabase()[name].getSchema());
	newRel.setValues(db.getDatabase()[name].getValues());

	vector<Parameter> params = pred.getParams();
	for (unsigned int i = 0; i < params.size(); i++) {
		string value = params[i].getParam();
		if (domain.find(value) == domain.end()) {
			if (value.at(0) == '\'') {
				newRel.clear();
				return newRel;
			}
			getID(value, i);
		}

		else {
			newRel = newRel.select(i, value);
		}
	}

	newRel = newRel.selectDupe(IDs);
	for (unsigned int i = 0; i < IDs.size(); i++) {
		newRel = newRel.rename(IDs[i].second, IDs[i].first);
	}
	newRel = newRel.project(IDs);
	return newRel;
}

void DatabaseManager::addID(string name, int num) {
	pair<string, vector<int>> id;
	id.first = name;
	id.second.push_back(num);
	IDs.push_back(id);
}

void DatabaseManager::getID(string name, int num) {
	if (IDs.size() == 0) {
		addID(name, num);
	}

	else {
		bool addable = true;
		for (unsigned int i = 0; i < IDs.size(); i++) {
			if (IDs[i].first == name) {
				IDs[i].second.push_back(num);
				addable = false;
			}
		}

		if (addable) {
			addID(name, num);
		}
	}
}