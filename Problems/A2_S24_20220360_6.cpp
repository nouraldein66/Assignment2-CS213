// File: A2_S24_20220360_3.cpp
// Purpose: Solving the third problem
// Author: Dr. Mohammed El-Ramly
// Section: S24
// ID: 20220360
// TA: To be determined
// Date: 27 Oct 2023

#include <iostream>
#include <math.h>
using namespace std;

void binaryPrint(int n){
    if(n == 0){
        cout << 0;
        return;
    }
    binaryPrint(n/2);
    cout << n%2;
}

void numbers(string prefix, int k){
    if(k == 0){
        cout << prefix <<'\n';
        return;
    }

    numbers(prefix+'0',k-1);
    numbers(prefix+'1',k-1);
}



int main(){
    int n;
    cin >> n;
    binaryPrint(n);
    string pre;
    cin >> pre >> n;
    numbers(pre,n);
}