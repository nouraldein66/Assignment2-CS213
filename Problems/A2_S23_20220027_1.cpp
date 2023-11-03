// File: A2_S23_20220027_1.cpp
// Purpose: Solving problem 1 in sheet 1
// Author: Ahmed Abdelnabi
// Section: S23
// ID: 20220027
// TA: Muhammad Talaat
// Date: 3 Nov 2023

#include <bits/stdc++.h>

using namespace std;

int main() {
    string input;
    getline(cin, input);

    vector<string> words;
    istringstream iss(input); // Create a stringstream from the input string

    string word;
    while (iss >> word) { // When ">>" is used to extract data from a stream, it ignores whitespaces, and returns false when it's the end of the stream, ending the while loop.
        words.push_back(word);
    }

    words[0][0] = toupper(words[0][0]);

    for (int i {1}; i < words[0].size(); ++i) {
        words[0][i] = tolower(words[0][i]);
    }

    for (int i {1}; i < words.size(); ++i) {
        for (int j {0}; j < words[i].size(); ++j) {
            if (isalpha(words[i][j])) {
                words[i][j] = tolower(words[i][j]);
            }
        }
    }

    for (int i {0}; i < words.size(); ++i) {
        cout << words[i] << " ";
    }


    return 0;
}
