// File: A2_S23_20220027_1.cpp
// Purpose: Solving problem 10 in sheet 1
// Author: Ahmed Abdelnabi
// Section: S23
// ID: 20220027
// TA: Muhammad Talaat
// Date: 4 Nov 2023

#include <bits/stdc++.h>

using namespace std;

int main() {

    ifstream inputFile("input_message.txt");
    ifstream lookupFile("lookup_table.txt");
    ofstream outputFile("output_message.txt");

    map <string,string> wordReplace;
    string word, alternative;

    while (lookupFile >> word >> alternative) {
        wordReplace[word] = alternative;
    }

    string content, line;
    while (getline(inputFile, line)) {
        content += line + '\n';
    }

    for (auto const &pair: wordReplace) {
        size_t pos {0};
        while ((pos = content.find(pair.first, pos)) != string::npos) {
            content.replace(pos, pair.first.length(), pair.second);
            pos += pair.second.length();
        }
    }

    outputFile << content;

    lookupFile.close();
    inputFile.close();
    outputFile.close();

    return 0;
}