#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <set>
#include <algorithm>
#include <unordered_map>

class HashTable {
	int loadCount = 0;
	int tabSize;
	int hasher(std::string* in);
	void rehash();
	bool find(std::string* in);
	std::vector<std::vector<std::string>> data;
	int score(std::string* in);
	void checkPermutations(int r, int n, char* arry, std::set<std::string>* valid);
public:
	void search(std::string* in);
	HashTable(int n = 5);
	void insert(std::string* in);
	
};