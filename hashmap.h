#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

class Unscrambler {
	unordered_map<string, int> dictionary;
	void checkPermutations(int r, int n, char* arry, set<string>* valid);
	int score(string in);
public:
	void addWord(string in);
	void unscramble(string in);
};