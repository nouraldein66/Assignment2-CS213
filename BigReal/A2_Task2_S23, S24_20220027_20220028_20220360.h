// File: A2_Task2_S23, S24_20220027_20220028_20220360.h
// Purpose: Making a class for big real numbers that ordinary C++ data types cannot handle
// Authors: Nour Aldeen, Ahmed Alaa Aldeen, Ahmed Abdelnabi
// Section: S23, S24
// ID: 20220360, 20220028, 20220027
// TA: Muhammad Talaat
// Date: 5 Nov 2023

#ifndef _BIGREAL_H
#define _BIGREAL_H

#include <bits/stdc++.h>

using namespace std;

class BigReal {
    friend istream &operator>>(istream &in, BigReal &a);
    friend  ostream &operator<<(ostream &out, const BigReal &a);
private:
    string s;
public:
    bool isValid();
    bool isNeg();
    bool operator==(const BigReal &a) const;
    BigReal operator+(BigReal &a);
    BigReal operator-(BigReal &a);
    bool operator<(BigReal &another_real);
    bool operator>(BigReal &anotherreal);
    void setNum(string s);
    string getNum() const;
};

bool compare_fraction(string s1, string s2);

#endif //_BIGREAL_H
