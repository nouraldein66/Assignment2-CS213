#include <bits/stdc++.h>
using namespace std;

class BigReal {
private:
    string s;
public:
//    bool isValid();
    bool isNeg();
   friend istream &operator >>(istream &in , BigReal &a);
   friend  ostream &operator<<(ostream &out , BigReal& a);
   bool operator == (const BigReal & a)const;
   BigReal operator+(BigReal& a);
};



