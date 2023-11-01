//
// Created by Ahmed Alaaeldin on 11/1/2023.
//

#include "BigReal.h"

bool BigReal::isNeg() {
    return (s[0] == '-');
}

string sum(string &a,string &b){
    string c="";
    if(a.length()>b.length())swap(a,b);
    int n1= a.length(),n2= b.length(),carry{},sum{},d=n2-n1;
    for(int i= n1-1;i>=0;i--){
        sum=(b.at(i+d)-'0')+(a.at(i)-'0')+carry;
        c.push_back(sum%10 +'0');
        carry = sum/10;
    }
    for(int i= n2-n1-1;i>=0;i--){
        sum=(b[i]-'0')+carry;
        c.push_back(sum%10 +'0');
        carry = sum/10;
    }
    if(carry)c.push_back(carry+'0');
    reverse (c.begin(),c.end());
    return c;
}

istream &operator>>(istream &in, BigReal &a) {
    cin >> a.s;
    return in;
}

bool BigReal::operator==(const BigReal &a) const {
   string first_before_dot = "" , first_after_dot = "" , second_before_dot = "" , second_after_dot = "";
   int sz1 = (int)this->s.size() , sz2 = (int)a.s.size();
   int i = 0;
   for(; i < sz1 ; i++)
   {
       if(this->s[i] == '.')
           break;
       if(first_before_dot.empty() && this->s[i] == '0')
           continue;
       first_before_dot += this->s[i];
   }
   ++i;
   for(; i < sz1 ; i++)
       first_after_dot += this->s[i];
   while(!first_after_dot.empty() && first_after_dot.back() == '0')
          first_after_dot.pop_back();

   i = 0;
   for(; i < sz2 ; ++i)
   {
       if(a.s[i] == '.')
             break;
       if(second_before_dot.empty() && a.s[i] == '0')
           continue;
       second_before_dot += a.s[i];
   }
   ++i;
   for(; i < sz2 ; ++i)
         second_after_dot += a.s[i];
   while(!second_after_dot.empty() && second_after_dot.back() == '0')
         second_after_dot.pop_back();
 return (first_before_dot == second_before_dot && first_after_dot == second_after_dot);
}

BigReal BigReal::operator+(BigReal &a) {
    BigReal ans;
       if(!(a.isNeg() ^ (this->s[0] == '-') ) ) {
           string first_before_dot = "", first_after_dot = "", second_before_dot = "", second_after_dot = "";
           int sz1 = (int) this->s.size(), sz2 = (int) a.s.size();
           int i = 0;
           for (; i < sz1; i++) {
               if (this->s[i] == '.')
                   break;
               if (first_before_dot.empty() && this->s[i] == '0' )
                   continue;
               if(this->s[i] != '-')
                  first_before_dot += this->s[i];
           }
           ++i;
           for (; i < sz1; i++)
                 if(this->s[i] != '-')
                  first_after_dot += this->s[i];
           while (!first_after_dot.empty() && first_after_dot.back() == '0')
               first_after_dot.pop_back();

           i = 0;
           for (; i < sz2; ++i) {
               if (a.s[i] == '.')
                   break;
               if (second_before_dot.empty() && a.s[i] == '0' )
                   continue;
               if(a.s[i] != '-')
                 second_before_dot += a.s[i];
           }
           ++i;
           for (; i < sz2; ++i)
               if(a.s[i] != '-')
                 second_after_dot += a.s[i];
           while (!second_after_dot.empty() && second_after_dot.back() == '0')
               second_after_dot.pop_back();

           while (first_after_dot.size() < second_after_dot.size())
               first_after_dot += '0';
           while (second_after_dot.size() < first_after_dot.size())
               second_after_dot += '0';

           string frac = sum(first_after_dot, second_after_dot);
           string integer = sum(first_before_dot, second_before_dot);

           if (frac.size() > second_after_dot.size()) {
               string b = "1";
               integer = sum(integer, b);
               frac.erase(frac.begin());
           }

           ans.s = "";
           if(a.isNeg())ans.s = "-";
           ans.s += integer + '.' + frac;
           if (frac.empty())
               ans.s.pop_back();


       }
    return ans;
}

ostream &operator<<(ostream &out, BigReal &a) {
    cout<<a.s;
    return out;
}
