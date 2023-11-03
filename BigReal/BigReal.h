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
