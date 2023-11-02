#include "BigReal.h"

bool BigReal::isNeg() {
    return (s[0] == '-');
}

string sum(string &a, string &b){
    string c = "";

    if (a.length() > b.length()) {
        swap(a,b);
    }

    int n1 = a.length();
    int n2= b.length();
    int carry = 0;
    int sum = 0;
    int d = n2-n1;

    for (int i = n1 - 1; i >= 0; --i) {

        sum = (b.at(i + d) - '0') + (a.at(i) - '0') + carry;
        c.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    for (int i = n2 - n1 - 1; i >= 0; --i) {
        sum = (b[i] - '0') + carry;
        c.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry) {
        c.push_back(carry + '0');
    }

    reverse(c.begin(),c.end());
    return c;
}

istream &operator>>(istream &in, BigReal &a) {
    cin >> a.s;
    return in;
}

bool BigReal::operator==(const BigReal &a) const {
    string first_before_dot = "";
    string first_after_dot = "";
    string second_before_dot = "";
    string second_after_dot = "";
    int sz1 = (int)this->s.size();
    int sz2 = (int)a.s.size();
    int i = 0;

    for (; i < sz1; ++i) {
        if (this->s[i] == '.') {
            break;
        }

        if (first_before_dot.empty() && this->s[i] == '0') {
            continue;
        }
        first_before_dot += this->s[i];
    }
    ++i;

    for (; i < sz1; ++i) {
        first_after_dot += this->s[i];
    }

    while (!first_after_dot.empty() && first_after_dot.back() == '0') {
        first_after_dot.pop_back();
    }

    i = 0;

    for (; i < sz2; ++i) {
        if (a.s[i] == '.') {
            break;
        }

        if (second_before_dot.empty() && a.s[i] == '0') {
            continue;
        }
        second_before_dot += a.s[i];
    }

    ++i;

    for(; i < sz2; ++i) {
        second_after_dot += a.s[i];
    }

    while (!second_after_dot.empty() && second_after_dot.back() == '0') {
        second_after_dot.pop_back();
    }
    return (first_before_dot == second_before_dot && first_after_dot == second_after_dot);
}

BigReal BigReal::operator+(BigReal &a) {
    BigReal ans;

    if (!(a.isNeg() ^ (this->s[0] == '-'))) {
        string first_before_dot = "";
        string first_after_dot = "";
        string second_before_dot = "";
        string second_after_dot = "";
        int sz1 = (int)this->s.size();
        int sz2 = (int) a.s.size();
        int i = 0;

        for (; i < sz1; ++i) {
            if (this->s[i] == '.') {
                break;
            }

            if (first_before_dot.empty() && this->s[i] == '0') {
                continue;
            }

            if (this->s[i] != '-') {
                first_before_dot += this->s[i];
            }
        }

        ++i;

        for (; i < sz1; ++i) {
            if (this->s[i] != '-') {
                first_after_dot += this->s[i];
            }
        }
        while (!first_after_dot.empty() && first_after_dot.back() == '0') {
            first_after_dot.pop_back();
        }

        i = 0;
        for (; i < sz2; ++i) {
            if (a.s[i] == '.') {
                break;
            }
            if (second_before_dot.empty() && a.s[i] == '0') {
                continue;
            }

            if (a.s[i] != '-') {
                second_before_dot += a.s[i];
            }
        }

        ++i;

        for (; i < sz2; ++i) {
            if (a.s[i] != '-') {
                second_after_dot += a.s[i];
            }
        }

        while (!second_after_dot.empty() && second_after_dot.back() == '0') {
            second_after_dot.pop_back();
        }

        while (first_after_dot.size() < second_after_dot.size()) {
            first_after_dot += '0';
        }

        while (second_after_dot.size() < first_after_dot.size()) {
            second_after_dot += '0';
        }

        string frac = sum(first_after_dot, second_after_dot);
        string integer = sum(first_before_dot, second_before_dot);

        if (frac.size() > second_after_dot.size()) {
            string b = "1";
            integer = sum(integer, b);
            frac.erase(frac.begin());
        }

        ans.s = "";

        if (a.isNeg()) {
            ans.s = "-";
        }

        ans.s += integer + '.' + frac;

        if (frac.empty()) {
            ans.s.pop_back();
        }
    }
    return ans;
}

bool BigReal::operator<(BigReal &another_real)  {
    //isValid(another_real);

    if (BigReal::isNeg() && !another_real.isNeg()) {      //first real is negative, other is positive
        return true;
    }


    if (!BigReal::isNeg() && another_real.isNeg()) { //first real is pos, the other is neg
        return false;
    } else if (s[0] == '-' && another_real.s[0] == '-') {  //if both are negative
        /* here we'll create two strings for each number, a string for first half of the number
         * and a string for second half of the number which is the half after the floating point
         * our goal is to compare the halves separately, if the first half of one of the numbers greater than
         * the other then we don't need to compare the floating halves, we'll only compare them when first half
         * of both numbers is equal
         */

        string firstHalf1 = "";
        string floatingHalf1 = "";
        string firstHalf2 = "";
        string floatingHalf2 = "";
        int index = s.size();
        //first number non-floating half

        for (int i = 1; i < index; ++i) {
            if (s[i] == '.') {  //floating point
                index = i + 1;  //index will start from the number after the floating point
                break;
            }
            if (s[i] == '0' && firstHalf1.empty()) {
                continue;
            } else {
                firstHalf1 += s[i];
            }
        }

        //first number floating half
        for (int i = index; i < s.size(); ++i) {
            floatingHalf1 += s[i];
        }
        while (!floatingHalf1.empty() && floatingHalf1.back() == '0') {
            floatingHalf1.pop_back();
        }

        //second number non-floating half
        index = another_real.s.size();

        for (int i = 1; i < index; ++i) {
            if (another_real.s[i] == '.') {
                index = i + 1;
                break;
            }
            if (another_real.s[i] == '0' && firstHalf2.empty()) {
                continue;
            } else {
                firstHalf2 += another_real.s[i];
            }
        }

        //second number floating half
        for (int i = index; i < another_real.s.size(); ++i) {
            floatingHalf2 += another_real.s[i];
        }

        while (!floatingHalf2.empty() && floatingHalf2.back() == '0') {
            floatingHalf2.pop_back();
        }

        //a quick check to see if the numbers are totally equal
        if (firstHalf1 + floatingHalf1 == firstHalf2 + floatingHalf2) {
            return false;
        }

        //now to compare: first we begin with non-floating halves
        if (firstHalf1.size() > firstHalf2.size()) {
            return true;
        }
        if (firstHalf1.size() < firstHalf2.size()) {
            return false;
        }
        if (firstHalf1 != firstHalf2) {
            for (int i = 0; i < firstHalf1.size(); ++i) {
                if (firstHalf1[i] == firstHalf2[i]) {
                    continue;
                } else {
                    if (firstHalf1[i] > firstHalf2[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        } else {   //the case for checking the floating halves
            if (floatingHalf1.size() > floatingHalf2.size()) {
                return true;
            }
            if (floatingHalf1.size() < floatingHalf2.size()) {
                return false;
            }
            if (floatingHalf1 != floatingHalf2) {
                for (int i = 0; i < floatingHalf1.size(); ++i) {
                    if (floatingHalf1[i] == floatingHalf2[i]) {
                        continue;
                    } else {
                        if (floatingHalf1[i] > floatingHalf2[i]) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }

    } else {   //final case: if both numbers are positive, the same logic of the previous condition
        string firstHalf1 = "";
        string floatingHalf1 = "";
        string firstHalf2 = "";
        string floatingHalf2 = "";
        int index = s.size();
        //first number non-floating half

        for (int i = 0; i < index; ++i) {
            if (s[i] == '.') {  //floating point
                index = i + 1;  //index will start from the number after the floating point
                break;
            }
            if (s[i] == '0' && firstHalf1.empty()) {
                continue;
            } else {
                firstHalf1 += s[i];
            }
        }

        //first number floating half
        for (int i = index; i < s.size(); ++i) {
            floatingHalf1 += s[i];
        }

        while (!floatingHalf1.empty() && floatingHalf1.back() == '0') {
            floatingHalf1.pop_back();
        }

        //second number non-floating half
        index = another_real.s.size();

        for (int i = 0; i < index; ++i) {
            if (another_real.s[i] == '.') {
                index = i + 1;
                break;
            }

            if (another_real.s[i] == '0' && firstHalf2.empty()) {
                continue;
            } else {
                firstHalf2 += another_real.s[i];
            }
        }

        //second number floating half
        for (int i = index; i < another_real.s.size(); ++i) {
            floatingHalf2 += another_real.s[i];
        }

        while (!floatingHalf2.empty() && floatingHalf2.back() == '0') {
            floatingHalf2.pop_back();
        }

        //a quick check to see if the numbers are totally equal
        if (firstHalf1 + floatingHalf1 == firstHalf2 + floatingHalf2) {
            return false;
        }

        //now to compare: first we begin with non-floating halves
        if (firstHalf1.size() > firstHalf2.size()) {
            return false;
        }
        if (firstHalf1.size() < firstHalf2.size()) {
            return true;
        }
        if (firstHalf1 != firstHalf2) {
            for (int i = 0; i < firstHalf1.size(); ++i) {
                if (firstHalf1[i] == firstHalf2[i]) {
                    continue;
                } else {
                    if(firstHalf1[i] > firstHalf2[i]) {
                        return false;
                    } else {
                        return true;
                    }
                }
            }
        } else {   //the case for checking the floating halves
            if (floatingHalf1.size() > floatingHalf2.size()) {
                return false;
            }
            if (floatingHalf1.size() < floatingHalf2.size()) {
                return true;
            }
            if (floatingHalf1 != floatingHalf2) {
                for (int i = 0; i < floatingHalf1.size(); ++i) {
                    if (floatingHalf1[i] == floatingHalf2[i]) {
                        continue;
                    } else {
                        if (floatingHalf1[i] > floatingHalf2[i]) {
                            return false;
                        } else {
                            return true;
                        }
                    }
                }
            }
        }
    }

}

bool BigReal::operator>(BigReal &anotherreal)  {
    //isValid(anotherreal);

    if (BigReal::isNeg() && !anotherreal.isNeg()) {  //first real is negative, other is positive
        return false;
    }


    if (!BigReal::isNeg() && anotherreal.isNeg()) { //first real is pos, the other is neg
        return true;
    } else if (s[0] == '-' && anotherreal.s[0] == '-') {  //if both are negative
        /* here we'll create two strings for each number, a string for first half of the number
         * and a string for second half of the number which is the half after the floating point
         * our goal is to compare the halves separately, if the first half of one of the numbers greater than
         * the other then we don't need to compare the floating halves, we'll only compare them when first half
         * of both numbers is equal
         */

        string firstHalf1 = "";
        string floatingHalf1 = "";
        string firstHalf2 = "";
        string floatingHalf2 = "";
        int index = s.size();
        //first number non-floating half

        for (int i = 1; i < index; ++i) {
            if (s[i] == '.') {  //floating point
                index = i + 1;  //index will start from the number after the floating point
                break;
            }
            if (s[i] == '0' && firstHalf1.empty()) {
                continue;
            } else {
                firstHalf1 += s[i];
            }
        }

        //first number floating half
        for (int i = index; i < s.size(); ++i) {
            floatingHalf1 += s[i];
        }

        while(!floatingHalf1.empty() && floatingHalf1.back() == '0') {
            floatingHalf1.pop_back();
        }

        //second number non-floating half
        index = anotherreal.s.size();
        for (int i = 1; i < index; ++i) {
            if (anotherreal.s[i] == '.') {
                index = i + 1;
                break;
            }
            if (anotherreal.s[i] == '0' && firstHalf2.empty()) {
                continue;
            } else {
                firstHalf2 += anotherreal.s[i];
            }
        }

        //second number floating half
        for (int i = index; i < anotherreal.s.size(); ++i) {
            floatingHalf2 += anotherreal.s[i];
        }

        while (!floatingHalf2.empty() && floatingHalf2.back() == '0') {
            floatingHalf2.pop_back();
        }

        //a quick check to see if the numbers are totally equal
        if (firstHalf1 + floatingHalf1 == firstHalf2 + floatingHalf2) {
            return false;
        }

        //now to compare: first we begin with non-floating halves
        if (firstHalf1.size() > firstHalf2.size()) {
            return false;
        }
        if (firstHalf1.size() < firstHalf2.size()) {
            return true;
        }
        if (firstHalf1 != firstHalf2) {
            for (int i = 0; i < firstHalf1.size(); ++i) {
                if (firstHalf1[i] == firstHalf2[i]) {
                    continue;
                } else {
                    if(firstHalf1[i] > firstHalf2[i]) {
                        return false;
                    } else {
                        return true;
                    }
                }
            }
        } else {   //the case for checking the floating halves
            if (floatingHalf1.size() > floatingHalf2.size()) {
                return false;
            }
            if (floatingHalf1.size() < floatingHalf2.size()) {
                return true;
            }
            if (floatingHalf1 != floatingHalf2) {
                for (int i = 0; i < floatingHalf1.size(); ++i) {
                    if (floatingHalf1[i] == floatingHalf2[i]) {
                        continue;
                    } else {
                        if (floatingHalf1[i] > floatingHalf2[i]) {
                            return false;
                        } else {
                            return true;
                        }
                    }
                }
            }
        }

    } else {   //final case: if both numbers are positive, the same logic of the previous condition
        string firstHalf1 = "";
        string floatingHalf1 = "";
        string firstHalf2 = "";
        string floatingHalf2 = "";
        int index = s.size();

        //first number non-floating half
        for (int i = 0; i < index; ++i) {
            if (s[i] == '.') {  //floating point
                index = i + 1;  //index will start from the number after the floating point
                break;
            }
            if (s[i] == '0' && firstHalf1.empty()) {
                continue;
            } else {
                firstHalf1 += s[i];
            }
        }

        //first number floating half
        for (int i = index; i < s.size(); ++i) {
            floatingHalf1 += s[i];
        }

        while(!floatingHalf1.empty() && floatingHalf1.back() == '0') {
            floatingHalf1.pop_back();
        }

        //second number non-floating half
        index = anotherreal.s.size();
        for (int i = 0; i < index; ++i) {
            if (anotherreal.s[i] == '.') {
                index = i + 1;
                break;
            }
            if (anotherreal.s[i] == '0' && firstHalf2.empty()) {
                continue;
            } else {
                firstHalf2 += anotherreal.s[i];
            }
        }

        //second number floating half
        for (int i = index; i < anotherreal.s.size(); ++i) {
            floatingHalf2 += anotherreal.s[i];
        }

        while (!floatingHalf2.empty() && floatingHalf2.back() == '0') {
            floatingHalf2.pop_back();
        }

        //a quick check to see if the numbers are totally equal
        if (firstHalf1 + floatingHalf1 == firstHalf2 + floatingHalf2) {
            return false;
        }

        //now to compare: first we begin with non-floating halves
        if (firstHalf1.size() > firstHalf2.size()) {
            return true;
        }
        if (firstHalf1.size() < firstHalf2.size()) {
            return false;
        }
        if (firstHalf1 != firstHalf2){
            for (int i = 0; i < firstHalf1.size(); ++i) {
                if (firstHalf1[i] == firstHalf2[i]) {
                    continue;
                } else {
                    if (firstHalf1[i] > firstHalf2[i]) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        } else {   //the case for checking the floating halves
            if(floatingHalf1.size() > floatingHalf2.size()) {
                return true;
            }
            if (floatingHalf1.size() < floatingHalf2.size()) {
                return false;
            }
            if (floatingHalf1 != floatingHalf2){
                for (int i = 0; i < floatingHalf1.size(); ++i) {
                    if(floatingHalf1[i] == floatingHalf2[i]) {
                        continue;
                    } else {
                        if (floatingHalf1[i] > floatingHalf2[i]) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }
    }
}

ostream &operator<<(ostream &out, const BigReal &a) {
    cout << a.s;
    return out;
}
