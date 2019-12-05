#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Implement an algorithm to find if a string has all unique characters.
// Implement with additional data structures, then without.
void function1() {
	int alpha_count[26] = { 0 };
	string s = "abcdefghijlmnopqrstuvwxyza";
	int index = 0;
	cout << "This is function for problem one" << endl;
	for (char c : s) {
		index = tolower(c) - 97;
		++alpha_count[index];
		if (alpha_count[index] > 1) {
			cout << "NOT UNIQUE" << endl;
			break;
		}
	}
	cout << endl;
	sort(s.begin(), s.end());
	for (string::iterator i = s.begin(); i != (s.end() - 1); ++i) {
		if (*i == (*(i+1))) {
			cout << "NOT UNIQUE" << endl;
			return;
		}
	}
	cout << "UNIQUE" << endl;
}

int main() {
	function1();
	return 0;
}
