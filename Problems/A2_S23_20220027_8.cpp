// File: A2_S23_20220027_8.cpp
// Purpose: Solving problem 8 in sheet 1
// Author: Ahmed Abdelnabi
// Section: S23
// ID: 20220027
// TA: Muhammad Talaat
// Date: 3 Nov 2023

#include <bits/stdc++.h>

using namespace std;

void pattern(int left, int length) {
   if (!length) {
       return;
   }

   pattern(left, length / 2); // Upper pattern

   for (int i {0}; i < left; ++i) {
       cout << "  ";
   }

   for (int i {0}; i < length; ++i) { // Central string
       cout << "* ";
   }

   cout << endl;

   pattern(left + length / 2, length / 2); // Lower pattern
}

int main() {
   int n;
   cin >> n; // n should be a power of 2
   pattern(0, n);

   return 0;
}
