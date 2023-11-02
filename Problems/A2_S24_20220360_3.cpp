// File: A2_S24_20220360_3.cpp
// Purpose: Solving the third problem
// Author: Dr. Mohammed El-Ramly
// Section: S24
// ID: 20220360
// TA: Muhammad Talaat
// Date: 27 Oct 2023

#include <iostream>
#include <vector>

using namespace std;


vector<string> split(string target, string delimeter){
    vector <string> v;
    string s = "";
    for (int i = 0; i < target.size(); ++i) {
        if(target[i] == delimeter[0]){
            v.push_back(s);
            s = "";
        }
        else
            s+=target[i];
    }
    if(s != "")
        v.push_back(s);
    return v;
}

int main(){
    vector <string> vec;
    string target, delimeter;
    getline(cin,target);
    getline(cin,delimeter);
    vec = split(target, delimeter);
    for(auto i : vec){
        cout << i << " ";
    }
}
