#include <iostream>
#include <cstring>
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

/* Write a method to replace all spaces in a string with "%20." Assume there
are enough space in the string for the additional characters. */

// My first go at the solution. Not as good as optimal.
// The right idea, however, I was recalculating the move var
// each time which is unneccessary work. I was also looping and
// moving over the characters, which is bad because if you pay
// attention to the actual index you can do direct indexing (much better).
void question3_v1() {
  // q3
  char s[18] = "Mr John Smith    ";
  int true_length = 13;
  int space_count = 0;
  int move_num = 0;

  for (int i = 0; i < true_length; ++i) {
    if (s[i] == ' ') {
      ++space_count;
    }
  }

  for (int i = true_length - 1; i >= 0; --i) {
    move_num = i + (space_count * 2);
    if (s[i] == ' ') {
      s[move_num] = '0';
      s[move_num - 1] = '2';
      s[move_num - 2] = '%';
      --space_count;
    } else {
      for (int j = i; j < move_num; ++j) {
        s[j + 1] = s[j];
      }
    }
  }
  cout << s << endl;
}

// C++ version of the optimal solution.
void question3_v2() {
  char s[18] = "Mr John Smith    ";
  int true_length = 13;
  int space_count = 0;
  int index = 0;

  for (int i = 0; i < true_length; ++i) {
    if (s[i] == ' ') {
      ++space_count;
    }
  }

  index = true_length + space_count * 2;
  for (int i = true_length - 1; i >= 0; --i) {
    if (s[i] == ' ') {
      s[index - 1] = '0';
      s[index - 2] = '2';
      s[index - 3] = '%';
      index -= 3;
    } else {
      s[index - 1] = s[i];
      --index;
    }
  }
  cout << s << endl;
}

int main() {
  question3_v2();
  return 0;
}
