// File: A2_S23_20220027_4.cpp
// Purpose: Solving problem 4 in sheet 1
// Author: Ahmed Abdelnabi
// Section: S23
// ID: 20220027
// TA: Muhammad Talaat
// Date: 3 Nov 2023

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> numbers;

    for (int i {2}; i <= N; ++i) {
        numbers.push_back(i);
    }

    for (int i {0}; i < numbers.size(); ++i) {
        if (numbers[i] == -1) {
            continue;
        }
        for (int j {i + 1}; j < numbers.size(); ++j) {
            if (numbers[j] % numbers[i] == 0) {
                numbers[j] = -1;
            }
        }
    }

    for (int x: numbers) {
        if (x != -1) {
            cout << x << " ";
        }
    }
    return 0;
}
