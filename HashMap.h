#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>

class Unscrambler {
	std::unordered_map<std::string, int> dictionary;
	void checkPermutations(int r, int n, char* arry, std::set<std::string>* valid);
	int score(std::string in);
public:
	void addWord(std::string in);
	void unscramble(std::string in);
};
