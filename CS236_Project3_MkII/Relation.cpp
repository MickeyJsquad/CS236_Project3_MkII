#include "Relation.h"

void Relation::clear() {
	name = "";
	schema.clear();
	values.clear();
}

Relation Relation::select(int num, string input) {
	Relation rel;
	rel.setName(name);
	rel.setSchema(schema);
	set<vector<string>>::iterator it;

	for (it = values.begin(); it != values.end(); it++) {
		vector<string> newVector = *it;
		if (newVector[num] == input) {
			rel.addValue(newVector);
		}
	}

	return rel;
}

Relation Relation::selectDupe(vector<pair<string, vector<int>>> IDs) {
	Relation rel;
	rel.setName(name);
	rel.setSchema(schema);
	bool isAdded = false;
	bool isDupe = false;
	vector<vector<string>> badTuples;

	if (IDs.size() == schema.size()) {
		rel.setValues(values);
		return rel;
	}

	for (unsigned int i = 0; i < IDs.size(); i++) {
		if (IDs[i].second.size() > 1) {
			bool hasFailed = true;
			isDupe = true;

			set<vector<string>>::iterator it;
			for (it = values.begin(); it != values.end(); it++) {
				bool selectable = true;

				vector<string> newVector = *it;
				for (unsigned int j = 0; j < badTuples.size(); j++) {
					if (badTuples[j] == newVector) {
						hasFailed = true;
					}
				}

				if (!hasFailed) {
					for (unsigned int k = 0; k < IDs[i].second.size(); k++) {
						if (k + 1 != IDs[i].second.size() && newVector[IDs[i].second[k]] != newVector[IDs[i].second[k + 1]]) {
							badTuples.push_back(newVector);
							selectable = false;
							break;
						}
					}

					if (selectable && goodTuple(IDs, newVector, i)) {
						rel.addValue(newVector);
						isAdded = true;
					}
				}
			}
		}
	}

	if (!isAdded && !isDupe) {
		rel.setValues(values);
	}

	return rel;
}

Relation Relation::project(vector<pair<string, vector<int>>> IDs) {
	Relation rel;
	rel.setName(name);
	vector<string> newSchema;

	for (unsigned int i = 0; i < IDs.size(); i++) {
		newSchema.push_back(IDs[i].first);
	}

	rel.setSchema(newSchema);
	set<vector<string>>::iterator it;

	for (it = values.begin(); it != values.end(); it++) {
		vector<string> tempVector = *it;
		vector<string> tempVals;

		for (unsigned int i = 0; i < IDs.size(); i++) {
			tempVals.push_back(tempVector[IDs[i].second[0]]);
		}

		rel.addValue(tempVals);
	}

	return rel;
}

Relation Relation::rename(vector<int> posNum, string input) {
	Relation rel;
	rel.setName(name);
	rel.setSchema(schema);
	rel.setValues(values);

	for (unsigned int i = 0; i < posNum.size(); i++) {
		rel.setAttribute(posNum[i], input);
	}

	return rel;
}

void Relation::toString() {
	set<vector<string>>::iterator it;
	for (it = values.begin(); it != values.end(); it++) {
		vector<string> newVector = *it;

		if (schema.size() != 0) {
			cout << " ";
		}

		for (unsigned int i = 0; i < schema.size(); i++) {
			cout << schema[i] << "=" << newVector[i];

			if (i + 1 != schema.size()) {
				cout << ", ";
			}
			else {
				cout << endl;
			}
		}
	}
}

bool Relation::goodTuple(vector<pair<string, vector<int>>> IDs, vector<string> tuple, int posNum) {
	bool selectable = true;

	for (unsigned int i = posNum + 1; i < IDs.size(); i++) {
		if (IDs[i].second.size() > 1) {
			for (unsigned int j = 0; j < IDs[i].second.size(); j++) {
				if (j + 1 != IDs[i].second.size() && tuple[IDs[i].second[j]] != tuple[IDs[i].second[j + 1]]) {
					selectable = false;
					break;
				}
			}
		}
	}

	return selectable;
}
