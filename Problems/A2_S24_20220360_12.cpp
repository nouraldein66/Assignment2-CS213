// File: A2_S24_20220360_3.cpp
// Purpose: Solving the third problem
// Author: Nour al-deen Alaa
// Section: S24
// ID: 20220360
// TA: Muhammad Talaat
// Date: 11 Nov 2023
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int main(){
    fstream file, targetfile;
    string s;
    file.open("Scams.txt", ios::out | ios::in);

    map <string , int> Points_Map;
    map <string, int> Occurences_Map;
    int i = 1;
    while(!file.eof()){
        getline(file,s);
        s[0] = tolower(s[0]);
        Points_Map.insert({s,i});
        Occurences_Map.insert({s,0});
        if(i < 3)
            ++i;
        else if(i > 1)
            --i;
    }


    targetfile.open("test.txt", ios::out | ios::in);
    int points = 0;
    string t;
    s = "";
    while (!targetfile.eof()){
        getline(targetfile,t, '\n');
        for (int j = 0; j <= t.size(); ++j) {
            if(t[j] == ' ' || j == t.size()){
                do {
                    switch (s.back() ) {
                        case ',':
                            s.pop_back();
                            break;
                        case '!':
                            s.pop_back();
                            break;
                        case '.':
                            s.pop_back();
                            break;
                        case '?':
                            s.pop_back();
                            break;
                        default:
                            break;
                    }
                }
                while (s.back() == ',' || s.back() == '.' || s.back() == '!' || s.back() == '?');
                transform(s.begin(), s.end(), s.begin(), ::tolower);
                if(Points_Map.find(s) != Points_Map.end()){
                    points += Points_Map[s];
                    Occurences_Map[s]++;
                    cout << s << "  Occurences: " << Occurences_Map[s] << "  Total points: " << points << endl;
            }
               s = "";
        }
            else
                s += t[j];

        }
    }
}