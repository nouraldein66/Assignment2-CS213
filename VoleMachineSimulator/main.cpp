#include <bits/stdc++.h>

using namespace  std;

int main() {
    string fileName;
    cin >> fileName;

    ifstream inputFile(fileName);

    string line;
    vector<string>instructions;

    while (getline(inputFile, line)) {
        instructions.emplace_back(line);
    }

    return 0;
}
