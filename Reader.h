#pragma once
#include "PointOnMap.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

PointOnMap split(string s) {
	PointOnMap result;
	int left = 0;
	vector<string> splittedStrings;
	while (left < s.size()) {
		int right = left;
		while (s[right] != ';')right++;
		splittedStrings.push_back(s.substr(left, right - left));
		left = right + 1;
	}
	result.Lat = stof(splittedStrings[0]);
	result.Long = stof(splittedStrings[1]);
	result.type = splittedStrings[2];
	result.subType = splittedStrings[3];
	result.name = splittedStrings[4];
	result.address = splittedStrings[5];
	result.converse();
	return result;
}

class Reader {
	string fileName;
public:
	Reader(string name) {
		fileName = name;
	}
	void readFromFile(vector<PointOnMap>& a) {
		ifstream in(fileName);
		ios_base::sync_with_stdio(false);
		string line;
		while (getline(in, line)) {
			a.push_back(split(line));
		}
	}
};