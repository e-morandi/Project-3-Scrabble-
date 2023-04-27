#include "HashTable.h"

// O(n) where n is the number of buckets
HashTable::HashTable(int n) {
	data.resize(n);
	tabSize = n;
}

// Adds a string to the hashtable in its hash bucket
// Avg. O(1), Worst O(n) where n is the number of buckets
void HashTable::insert(std::string* in) {
	
	// add string to vector at its hash index
	data[hasher(in)].push_back(*in);
	loadCount++;

	// rehash table if load factor is >= 0.8
	if ((float)loadCount / tabSize >= 0.8) {
		rehash();
	}
}

// Generates a reduced hash index for a given string
// O(n) where n is the length of argument "in"
int HashTable::hasher(std::string* in) {
	//returns reduced hash value of string
	return std::hash<std::string>{}(*in) % tabSize;
}

// Resizes the hashtable with double the size and copies the previous elements into their new buckets
// O(n) where n is the number of buckets (tabSize)
void HashTable::rehash() {
	//new array with size *= 2
	HashTable newData(tabSize * 2);
	//call insert on all previous nodes
	for (std::vector<std::string> v : data) {
		for (std::string s : v) {
			newData.insert(&s);
		}
	}
	//replace old array with new array
	data = newData.data;
	//update tabsize
	tabSize *= 2;
}

// Prints valid words that can be formed through any permutation of any combination of characters in the input string
// O(n) where n is the number of valid words formable
void HashTable::search(std::string* in) {
	
	std::set<std::string> valid_words;
	
	// O(1) string always 7 letters
	// std::sort(*in->begin(), *in->end());

	// r = 1 (p = 7)
	for (char a : *in) {
		std::string temp = "" + a;
		if (find(&temp)) {
			valid_words.emplace(temp);
		}
	}

	// r = 2 (p = 42)
	if (in->length() > 1) {
		for (int i = 0; i < 6; i++) {
			for (int j = 1; j < (7 - i); j++) {
				std::string temp = "";
				temp.push_back(in->at(i));
				temp.push_back(in->at(j + i));
				if (find(&temp)) {
					valid_words.emplace(temp);
				}
				temp = "";
				temp.push_back(in->at(j + i));
				temp.push_back(in->at(i));
				if (find(&temp)) {
					valid_words.emplace(temp);
				}
			}
		}
	}

	// r = 3 (p = 210)
	if (in->length() > 2) {
		for (int i = 0; i < 35; i++) {
			char temp[3] = {};
			if (i < 15) {
				temp[0] = in->at(0);
				if (i < 5) {
					temp[1] = in->at(1);
					temp[2] = in->at(i + 2);
				}
				else if (i < 9) {
					temp[1] = in->at(2);
					temp[2] = in->at(i - 2);
				}
				else if (i < 12) {
					temp[1] = in->at(3);
					temp[2] = in->at(i - 5);
				}
				else if (i < 14) {
					temp[1] = in->at(4);
					temp[2] = in->at(i - 7);
				}
				else if (i == 14) {
					temp[1] = in->at(5);
					temp[2] = in->at(6);
				}
			}
			else if (i < 25) {
				temp[0] = in->at(1);
				if (i < 19) {
					temp[1] = in->at(2);
					temp[2] = in->at(i - 12);
				}
				else if (i < 22) {
					temp[1] = in->at(3);
					temp[2] = in->at(i - 15);
				}
				else if (i < 24) {
					temp[1] = in->at(4);
					temp[2] = in->at(i - 17);
				}
				else if (i == 24) {
					temp[1] = in->at(5);
					temp[2] = in->at(6);
				}
			}
			else if (i < 31) {
				temp[0] = in->at(2);
				if (i < 28) {
					temp[1] = in->at(3);
					temp[2] = in->at(i - 21);
				}
				else if (i < 30) {
					temp[1] = in->at(4);
					temp[2] = in->at(i - 23);
				}
				else if (i == 30) {
					temp[1] = in->at(5);
					temp[2] = in->at(6);
				}
			}
			else if (i < 34) {
				temp[0] = in->at(3);
				if (i < 33) {
					temp[1] = in->at(4);
					temp[2] = in->at(i - 26);
				}
				else if (i == 33) {
					temp[1] = in->at(5);
					temp[2] = in->at(6);
				}
			}
			else if (i == 34) {
				temp[0] = in->at(4);
				temp[1] = in->at(5);
				temp[2] = in->at(6);
			}

			checkPermutations(3, 6, temp, &valid_words);
		}
	}

	// r = 4 (p = 840)
	if (in->length() > 3) {
		for (int i = 0; i < 35; i++) {
			char temp[4] = {};
			if (i < 20) {
				temp[0] = in->at(0);
				if (i < 10) {
					temp[1] = in->at(1);
					if (i < 4) {
						temp[2] = in->at(2);
						temp[3] = in->at(i + 3);
					}
					else if (i < 7) {
						temp[2] = in->at(3);
						temp[3] = in->at(i);
					}
					else if (i < 9) {
						temp[2] = in->at(4);
						temp[3] = in->at(i - 2);
					}
					else if (i == 9) {
						temp[2] = in->at(5);
						temp[3] = in->at(6);
					}
				}
				else if (i < 16) {
					temp[1] = in->at(2);
					if (i < 13) {
						temp[2] = in->at(3);
						temp[3] = in->at(i - 6);
					}
					else if (i < 15) {
						temp[2] = in->at(4);
						temp[3] = in->at(i - 8);
					}
					else if (i == 15) {
						temp[2] = in->at(5);
						temp[3] = in->at(6);
					}
				}
				else if (i < 19) {
					temp[1] = in->at(3);
					if (i < 18) {
						temp[2] = in->at(4);
						temp[3] = in->at(i - 11);
					}
					else if (i == 18) {
						temp[2] = in->at(5);
						temp[3] = in->at(6);
					}
				}
				else if (i == 19) {
					temp[1] = in->at(4);
					temp[2] = in->at(5);
					temp[3] = in->at(6);
				}
			}
			else if (i < 30) {
				temp[0] = in->at(1);
				if (i < 26) {
					temp[1] = in->at(2);
					if (i < 23) {
						temp[2] = in->at(3);
						temp[3] = in->at(i - 16);
					}
					else if (i < 25) {
						temp[2] = in->at(4);
						temp[3] = in->at(i - 18);
					}
					else if (i == 25) {
						temp[2] = in->at(5);
						temp[3] = in->at(6);
					}
				}
				else if (i < 29) {
					temp[1] = in->at(3);
					if (i < 28) {
						temp[2] = in->at(4);
						temp[3] = in->at(i - 21);
					}
					else if (i == 28) {
						temp[2] = in->at(5);
						temp[3] = in->at(6);
					}
				}
				else if (i == 29) {
					temp[1] = in->at(4);
					temp[2] = in->at(5);
					temp[3] = in->at(6);
				}
			}
			else if (i < 34) {
				temp[0] = in->at(2);
				if (i < 33) {
					temp[1] = in->at(3);
					if (i < 32) {
						temp[2] = in->at(4);
						temp[3] = in->at(i - 25);
					}
					else if (i == 32) {
						temp[2] = in->at(5);
						temp[3] = in->at(6);
					}
				}
				else if (i == 33) {
					temp[1] = in->at(4);
					temp[2] = in->at(5);
					temp[3] = in->at(6);
				}
			}
			else if (i == 34) {
				temp[0] = in->at(3);
				temp[1] = in->at(4);
				temp[2] = in->at(5);
				temp[3] = in->at(6);
			}

			checkPermutations(4, 24, temp, &valid_words);
		}
	}

	// r = 5 (p = 2520)
	if (in->length() > 4) {
		for (int i = 0; i < 21; i++) {
			char temp[5];
			if (i < 15) {
				temp[0] = in->at(0);
				if (i < 10) {
					temp[1] = in->at(1);
					if (i < 6) {
						temp[2] = in->at(2);
						if (i < 3) {
							temp[3] = in->at(3);
							temp[4] = in->at(i + 4);
						}
						else if (i < 5) {
							temp[3] = in->at(4);
							temp[4] = in->at(i + 2);
						}
						else if (i == 5) {
							temp[3] = in->at(5);
							temp[4] = in->at(6);
						}
					}
					else if (i < 9) {
						temp[2] = in->at(3);
						if (i < 8) {
							temp[3] = in->at(4);
							temp[4] = in->at(i - 1);
						}
						else if (i == 8) {
							temp[3] = in->at(5);
							temp[4] = in->at(6);
						}
					}
					else if (i == 9) {
						temp[2] = in->at(4);
						temp[3] = in->at(5);
						temp[4] = in->at(6);
					}
				}
				else if (i < 14) {
					temp[1] = in->at(2);
					if (i < 13) {
						temp[2] = in->at(3);
						if (i < 12) {
							temp[3] = in->at(4);
							temp[4] = in->at(i - 5);
						}
						else if (i == 12) {
							temp[3] = in->at(5);
							temp[4] = in->at(6);
						}
					}
					else if (i == 13) {
						temp[2] = in->at(4);
						temp[3] = in->at(5);
						temp[4] = in->at(6);
					}
				}
				else if (i == 14) {
					temp[1] = in->at(3);
					temp[2] = in->at(4);
					temp[3] = in->at(5);
					temp[4] = in->at(6);
				}
			}
			else if (i < 20) {
				temp[0] = in->at(1);
				if (i < 19) {
					temp[1] = in->at(2);
					if (i < 18) {
						temp[2] = in->at(3);
						if (i < 17) {
							temp[3] = in->at(5);
							temp[4] = in->at(i - 10);
						}
						else if (i == 17) {
							temp[3] = in->at(5);
							temp[4] = in->at(6);
						}
					}
					else if (i == 18) {
						temp[2] = in->at(4);
						temp[3] = in->at(5);
						temp[4] = in->at(6);
					}
				}
				else if (i == 19) {
					temp[1] = in->at(3);
					temp[2] = in->at(4);
					temp[3] = in->at(5);
					temp[4] = in->at(6);
				}
			}
			else if (i == 20) {
				temp[0] = in->at(2);
				temp[1] = in->at(3);
				temp[2] = in->at(4);
				temp[3] = in->at(5);
				temp[4] = in->at(6);
			}

			checkPermutations(5, 120, temp, &valid_words);
		}
	}

	// r = 6 (p = 5040)
	if (in->length() > 5) {
		for (int i = 0; i < 7; i++) {
			char temp[6];
			switch (i) {
			case 0:
				temp[0] = in->at(0);
				temp[1] = in->at(1);
				temp[2] = in->at(2);
				temp[3] = in->at(3);
				temp[4] = in->at(4);
				temp[5] = in->at(5);
				break;
			case 1:
				temp[0] = in->at(0);
				temp[1] = in->at(1);
				temp[2] = in->at(2);
				temp[3] = in->at(3);
				temp[4] = in->at(4);
				temp[5] = in->at(6);
				break;
			case 2:
				temp[0] = in->at(0);
				temp[1] = in->at(1);
				temp[2] = in->at(2);
				temp[3] = in->at(3);
				temp[4] = in->at(5);
				temp[5] = in->at(6);
				break;
			case 3:
				temp[0] = in->at(0);
				temp[1] = in->at(1);
				temp[2] = in->at(2);
				temp[3] = in->at(4);
				temp[4] = in->at(5);
				temp[5] = in->at(6);
				break;
			case 4:
				temp[0] = in->at(0);
				temp[1] = in->at(1);
				temp[2] = in->at(3);
				temp[3] = in->at(4);
				temp[4] = in->at(5);
				temp[5] = in->at(6);
				break;
			case 5:
				temp[0] = in->at(0);
				temp[1] = in->at(2);
				temp[2] = in->at(3);
				temp[3] = in->at(4);
				temp[4] = in->at(5);
				temp[5] = in->at(6);
				break;
			case 6:
				temp[0] = in->at(1);
				temp[1] = in->at(2);
				temp[2] = in->at(3);
				temp[3] = in->at(4);
				temp[4] = in->at(5);
				temp[5] = in->at(6);
				break;
			}
			checkPermutations(6, 720, temp, &valid_words);
		}
	}

	// r = 7 (p = 5040)
	if (in->length() > 6) {
		char temp[7] = {};
		for (int i = 0; i < 7; i++) {
			temp[i] = in->at(i);
		}
		checkPermutations(7, 5040, temp, &valid_words);
	}

	for (auto it : valid_words) {
		std::cout << it << " " << score(&it) << std::endl;
	}
}

// Checks if a string is present in the hashmap through linear probing
// Avg. O(1), Worst O(n * m) where n is the size of the vector in the corresponding bucket and m is the length of argument "in"
bool HashTable::find(std::string* in) {
	
	for (std::string s : data[hasher(in)]) {
		if (*in == s) {
			return true;
		}
	}

	return false;
}

// Calculates score for a given string using set point values
// O(1)
int HashTable::score(std::string* in) {
	int score = 0;

	std::unordered_map<char, int> point_values = {
	{'A', 1},
	{'B', 3},
	{'C', 3},
	{'D', 2},
	{'E', 1},
	{'F', 4},
	{'G', 2},
	{'H', 4},
	{'I', 1},
	{'J', 8},
	{'K', 5},
	{'L', 1},
	{'M', 3},
	{'N', 1},
	{'O', 1},
	{'P', 3},
	{'Q', 10},
	{'R', 1},
	{'S', 1},
	{'T', 1},
	{'U', 1},
	{'V', 4},
	{'W', 4},
	{'X', 8},
	{'Y', 4},
	{'Z', 10}
	};

	for (char a : *in) {
		score += point_values[a];
	}

	return score;
}

// Checks if each permutation of a combination of characters exists in the hashtable and pushes to valid word set
// O(n * (m + k)) where n is the number of permutations, m is the length of the combination, and k is the number of valid words found
void HashTable::checkPermutations(int r, int n, char* arry, std::set<std::string>* valid) {

	for (int j = 0; j < n; j++) {
		std::string temp;
		for (int i = 0; i < r; i++) {
			temp.push_back(arry[i]);
		}
		if (find(&temp)) {
			valid->emplace(temp);
		}
		std::next_permutation(arry, arry + r);
	}

}