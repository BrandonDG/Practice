#include <iostream>
#include <bits/stdc++.h>

using namespace std;
/* Implement an algorithm to determine if a string has all unique characters */

// Pre-sort (representation change)
void question1_v1() {
  string s = "abcdefgh";
  sort(s.begin(), s.end());
  for (string::iterator it = s.begin(); it != (s.end() - 1); it++) {
    if (*it == *(it + 1)) {
      cout << "NOT UNIQUE" << endl;
      return;
    }
  }
  cout << "UNIQUE" << endl;
}

// Brute force. Bad time, good space.
void question1_v2() {
  string s = "abcdefgha";
  for (string::iterator it1 = s.begin(); it1 != (s.end() - 1); ++it1) {
    for (string::iterator it2 = it1 + 1; it2 != s.end(); ++it2) {
      if (*it1 == *it2) {
        cout << "NOT UNIQUE" << endl;
        return;
      }
    }
  }
  cout << "UNIQUE" << endl;
}

// Record using a boolean array.
void question1_v3() {
  string s = "abcdeghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY";
  int index = 0;
  bool track_array[128] = { false };

  if (s.length() > 128) {
    cout << "NOT UNIQUE" << endl;
    return;
  }

  for (string::iterator it = s.begin(); it != s.end(); ++it) {
    index = *it;
    if (track_array[index]) {
      cout << "NOT UNIQUE" << endl;
      return;
    }
    track_array[index] = true;
  }
  cout << "UNIQUE" << endl;
}

/* Given two strings, write a method to decide if one is a permutation of
the other */

// Record using int value of each character. Would run into issues
// if it is a really big string, storage issues =.
void question2_v1() {
  string s1 = "abcdefg";
  string s2 = "gafbecd";
  int s1_count, s2_count;
  s1_count = s2_count = 0;

  if (s1.length() != s2.length()) {
    cout << "NOT PERMUTATION" << endl;
    return;
  }

  string::iterator it1, it2;
  for (it1 = s1.begin(), it2 = s2.begin(); it1 != s1.end(); ++it1, ++it2) {
    s1_count += (int) *it1;
    s2_count += (int) *it2;
  }

  if (s1_count == s2_count) {
    cout << "PERMUTATION" << endl;
  } else {
    cout << "NOT PERMUTATION" << endl;
  }
}

// Presort, then compare each one in order, manually.
void question2_v2() {
  string s1 = "abcdefg";
  string s2 = "gafbecd";

  if (s1.length() != s2.length()) {
    cout << "NOT PERMUTATION" << endl;
    return;
  }

  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());

  string::iterator it1, it2;
  for (it1 = s1.begin(), it2 = s2.begin(); it1 != s1.end(); ++it1, ++it2) {
    if (*it1 != *it2) {
      cout << "NOT PERMUTATION" << endl;
      return;
    }
  }

  cout << "PERMUTATION" << endl;
}

// Presort, then compare each one, using the string compare method.
void question2_v3() {
  string s1 = "abcdefg";
  string s2 = "gafbecd";

  if (s1.length() != s2.length()) {
    cout << "NOT PERMUTATION" << endl;
    return;
  }

  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());
  if (s1.compare(s2) == 0) {
    cout << "PERMUTATION" << endl;
  } else {
    cout << "NOT PERMUTATION" << endl;
  }
}

// Store the letter frequency in an array.
// Would be good, but would run into issues with Unicode vs
// ASCII as the array we would need would be rather large.
void question2_v4() {
  string s1 = "abcdefg";
  string s2 = "gafbecd";

  if (s1.length() != s2.length()) {
    cout << "NOT PERMUTATION" << endl;
    return;
  }

  int letter_count[128] = { 0 };

  for (char c : s1) {
    letter_count[(int)c]++;
  }

  for (char c : s2) {
    letter_count[(int)c]--;
    if (letter_count[(int)c] < 0) {
      cout << "NOT PERMUTATION" << endl;
      return;
    }
  }

  cout << "PERMUTATION" << endl;
}

int main() {
  question2_v4();
  return 0;
}
