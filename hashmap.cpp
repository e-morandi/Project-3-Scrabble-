#include "hashmap.h"

void Unscrambler::addWord(string in) {
	dictionary.insert(pair<string, int>(in, score(in)));
}

void Unscrambler::checkPermutations(int r, int n, char* arry, set<string>* valid) {

	for (int j = 0; j < n; j++) {
		string temp;
		for (int i = 0; i < r; i++) {
			temp.push_back(arry[i]);
		}
		if (dictionary.find(temp) != dictionary.end()) {
			valid->emplace(temp);
		}
		next_permutation(arry, arry + r);
	}

}

int Unscrambler::score(string in) {
	int score = 0;

	unordered_map<char, int> point_values = {
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

	for (char a : in) {
		score += point_values[a];
	}

	return score;
};

void Unscrambler::unscramble(string in) {

	sort(in.begin(), in.end());
	set<string> valid_words;

	/* r = 1
	for (int i = 0; i < 7; i++) {
		auto it = dictionary.find(in.substr(i, 1));
		if (it != dictionary.end()) {
			cout << it->first << " " << it->second << endl;
		}
	}
	*/

	// r = 2 (p = 42)
	for (int i = 0; i < 6; i++) {
		for (int j = 1; j < (7 - i); j++) {
			string temp = "";
			temp.push_back(in[i]);
			temp.push_back(in[j + i]);
			if (dictionary.find(temp) != dictionary.end()) {
				valid_words.emplace(temp);
			}
			temp = "";
			temp.push_back(in[j + i]);
			temp.push_back(in[i]);
			if (dictionary.find(temp) != dictionary.end()) {
				valid_words.emplace(temp);
			}
		}
	}

	// r = 3 (p = 210)
	for (int i = 0; i < 35; i++) {
		char temp[3] = {};
		if (i < 15) {
			temp[0] = in[0];
			if (i < 5) {
				temp[1] = in[1];
				temp[2] = in[i + 2];
			}
			else if (i < 9) {
				temp[1] = in[2];
				temp[2] = in[i - 2];
			}
			else if (i < 12) {
				temp[1] = in[3];
				temp[2] = in[i - 5];
			}
			else if (i < 14) {
				temp[1] = in[4];
				temp[2] = in[i - 7];
			}
			else if (i == 14) {
				temp[1] = in[5];
				temp[2] = in[6];
			}
		}
		else if (i < 25) {
			temp[0] = in[1];
			if (i < 19) {
				temp[1] = in[2];
				temp[2] = in[i - 12];
			}
			else if (i < 22) {
				temp[1] = in[3];
				temp[2] = in[i - 15];
			}
			else if (i < 24) {
				temp[1] = in[4];
				temp[2] = in[i - 17];
			}
			else if (i == 24) {
				temp[1] = in[5];
				temp[2] = in[6];
			}
		}
		else if (i < 31) {
			temp[0] = in[2];
			if (i < 28) {
				temp[1] = in[3];
				temp[2] = in[i - 21];
			}
			else if (i < 30) {
				temp[1] = in[4];
				temp[2] = in[i - 23];
			}
			else if (i == 30) {
				temp[1] = in[5];
				temp[2] = in[6];
			}
		}
		else if (i < 34) {
			temp[0] = in[3];
			if (i < 33) {
				temp[1] = in[4];
				temp[2] = in[i - 26];
			}
			else if (i == 33) {
				temp[1] = in[5];
				temp[2] = in[6];
			}
		}
		else if (i == 34) {
			temp[0] = in[4];
			temp[1] = in[5];
			temp[2] = in[6];
		}

		checkPermutations(3, 6, temp, &valid_words);
	}

	// r = 4 (p = 840)
	for (int i = 0; i < 35; i++) {
		char temp[4] = {};
		if (i < 20) {
			temp[0] = in[0];
			if (i < 10) {
				temp[1] = in[1];
				if (i < 4) {
					temp[2] = in[2];
					temp[3] = in[i + 3];
				}
				else if (i < 7) {
					temp[2] = in[3];
					temp[3] = in[i];
				}
				else if (i < 9) {
					temp[2] = in[4];
					temp[3] = in[i - 2];
				}
				else if (i == 9) {
					temp[2] = in[5];
					temp[3] = in[6];
				}
			}
			else if (i < 16) {
				temp[1] = in[2];
				if (i < 13) {
					temp[2] = in[3];
					temp[3] = in[i - 6];
				}
				else if (i < 15) {
					temp[2] = in[4];
					temp[3] = in[i - 8];
				}
				else if (i == 15) {
					temp[2] = in[5];
					temp[3] = in[6];
				}
			}
			else if (i < 19) {
				temp[1] = in[3];
				if (i < 18) {
					temp[2] = in[4];
					temp[3] = in[i - 11];
				}
				else if (i == 18) {
					temp[2] = in[5];
					temp[3] = in[6];
				}
			}
			else if (i == 19) {
				temp[1] = in[4];
				temp[2] = in[5];
				temp[3] = in[6];
			}
		}
		else if (i < 30) {
			temp[0] = in[1];
			if (i < 26) {
				temp[1] = in[2];
				if (i < 23) {
					temp[2] = in[3];
					temp[3] = in[i - 16];
				}
				else if (i < 25) {
					temp[2] = in[4];
					temp[3] = in[i - 18];
				}
				else if (i == 25) {
					temp[2] = in[5];
					temp[3] = in[6];
				}
			}
			else if (i < 29) {
				temp[1] = in[3];
				if (i < 28) {
					temp[2] = in[4];
					temp[3] = in[i - 21];
				}
				else if (i == 28) {
					temp[2] = in[5];
					temp[3] = in[6];
				}
			}
			else if (i == 29) {
				temp[1] = in[4];
				temp[2] = in[5];
				temp[3] = in[6];
			}
		}
		else if (i < 34) {
			temp[0] = in[2];
			if (i < 33) {
				temp[1] = in[3];
				if (i < 32) {
					temp[2] = in[4];
					temp[3] = in[i - 25];
				}
				else if (i == 32) {
					temp[2] = in[5];
					temp[3] = in[6];
				}
			}
			else if (i == 33) {
				temp[1] = in[4];
				temp[2] = in[5];
				temp[3] = in[6];
			}
		}
		else if (i == 34) {
			temp[0] = in[3];
			temp[1] = in[4];
			temp[2] = in[5];
			temp[3] = in[6];
		}

		checkPermutations(4, 24, temp, &valid_words);
	}

	// r = 5 (p = 2520)
	for (int i = 0; i < 21; i++) {
		char temp[5];
		if (i < 15) {
			temp[0] = in[0];
			if (i < 10) {
				temp[1] = in[1];
				if (i < 6) {
					temp[2] = in[2];
					if (i < 3) {
						temp[3] = in[3];
						temp[4] = in[i + 4];
					}
					else if (i < 5) {
						temp[3] = in[4];
						temp[4] = in[i + 2];
					}
					else if (i == 5) {
						temp[3] = in[5];
						temp[4] = in[6];
					}
				}
				else if (i < 9) {
					temp[2] = in[3];
					if (i < 8) {
						temp[3] = in[4];
						temp[4] = in[i - 1];
					}
					else if (i == 8) {
						temp[3] = in[5];
						temp[4] = in[6];
					}
				}
				else if (i == 9) {
					temp[2] = in[4];
					temp[3] = in[5];
					temp[4] = in[6];
				}
			}
			else if (i < 14) {
				temp[1] = in[2];
				if (i < 13) {
					temp[2] = in[3];
					if (i < 12) {
						temp[3] = in[4];
						temp[4] = in[i - 5];
					}
					else if (i == 12) {
						temp[3] = in[5];
						temp[4] = in[6];
					}
				}
				else if (i == 13) {
					temp[2] = in[4];
					temp[3] = in[5];
					temp[4] = in[6];
				}
			}
			else if (i == 14) {
				temp[1] = in[3];
				temp[2] = in[4];
				temp[3] = in[5];
				temp[4] = in[6];
			}
		}
		else if (i < 20) {
			temp[0] = in[1];
			if (i < 19) {
				temp[1] = in[2];
				if (i < 18) {
					temp[2] = in[3];
					if (i < 17) {
						temp[3] = in[5];
						temp[4] = in[i - 10];
					}
					else if (i == 17) {
						temp[3] = in[5];
						temp[4] = in[6];
					}
				}
				else if (i == 18) {
					temp[2] = in[4];
					temp[3] = in[5];
					temp[4] = in[6];
				}
			}
			else if (i == 19) {
				temp[1] = in[3];
				temp[2] = in[4];
				temp[3] = in[5];
				temp[4] = in[6];
			}
		}
		else if (i == 20) {
			temp[0] = in[2];
			temp[1] = in[3];
			temp[2] = in[4];
			temp[3] = in[5];
			temp[4] = in[6];
		}

		checkPermutations(5, 120, temp, &valid_words);
	}

	// r = 6 (p = 5040)
	for (int i = 0; i < 7; i++) {
		char temp[6];
		switch (i) {
		case 0:
			temp[0] = in[0];
			temp[1] = in[1];
			temp[2] = in[2];
			temp[3] = in[3];
			temp[4] = in[4];
			temp[5] = in[5];
			break;
		case 1:
			temp[0] = in[0];
			temp[1] = in[1];
			temp[2] = in[2];
			temp[3] = in[3];
			temp[4] = in[4];
			temp[5] = in[6];
			break;
		case 2:
			temp[0] = in[0];
			temp[1] = in[1];
			temp[2] = in[2];
			temp[3] = in[3];
			temp[4] = in[5];
			temp[5] = in[6];
			break;
		case 3:
			temp[0] = in[0];
			temp[1] = in[1];
			temp[2] = in[2];
			temp[3] = in[4];
			temp[4] = in[5];
			temp[5] = in[6];
			break;
		case 4:
			temp[0] = in[0];
			temp[1] = in[1];
			temp[2] = in[3];
			temp[3] = in[4];
			temp[4] = in[5];
			temp[5] = in[6];
			break;
		case 5:
			temp[0] = in[0];
			temp[1] = in[2];
			temp[2] = in[3];
			temp[3] = in[4];
			temp[4] = in[5];
			temp[5] = in[6];
			break;
		case 6:
			temp[0] = in[1];
			temp[1] = in[2];
			temp[2] = in[3];
			temp[3] = in[4];
			temp[4] = in[5];
			temp[5] = in[6];
			break;
		}
		checkPermutations(6, 720, temp, &valid_words);
	}

	// r = 7 (p = 5040)
	char temp[7] = {};
	for (int i = 0; i < 7; i++) {
		temp[i] = in[i];
	}
	checkPermutations(7, 5040, temp, &valid_words);

	for (auto& it : valid_words) {
		cout << it << " " << score(it) << endl;
	}
}