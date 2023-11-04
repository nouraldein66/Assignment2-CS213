// File: A2_S24_20220360_3.cpp
// Purpose: Solving the third problem
// Author: Dr. Mohammed El-Ramly
// Section: S24
// ID: 20220360
// TA: Muhammad Talaat
// Date: 27 Oct 2023//
#include <iostream>

using namespace std;

bool bears(int n){
    if(n == 42)
        return true;
    if(n < 42)
        return false;

    if(n%5 == 0){
        return bears(n-42);
    }
    else if( (n%4 == 0 || n%3 == 0) && (n%10 != 0 && (n%100)/10 != 0)){
        int val = (n%10)*((n%100)/10);
        return bears(n - val);
    }
    else if(n%2 == 0){
        return bears(n/2);
    }
    else{
        return false;
    }
}


int main(){
    int n;
    cin >> n;
    if(bears(n))
        cout << "True";
    else
        cout << "False";
}
