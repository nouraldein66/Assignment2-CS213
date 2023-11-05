// File: BigReal.cpp
// Purpose: Making a class for big real numbers that ordinary C++ data types cannot handle
// Authors: Nour Aldeen, Ahmed Alaa Aldeen, Ahmed Abdelnabi
// Section: S23, S24
// ID: 20220360, 20220028, 20220027
// TA: Muhammad Talaat
// Date: 5 Nov 2023

#include "BigReal.h"

bool BigReal::isNeg() {
    return (s[0] == '-');
}

bool BigReal::isValid() {
    int number_of_dots {0};
    bool no_digits {true};

    if (s[0] != '.' && s[0] != '-' && !isdigit(s[0]) && s[0] != '+') {
        return false;
    }

    for (int i {0}; i < s.size(); ++i) {
        if (isdigit(s[i])) {
            no_digits = false;
            break;
        }
    }

    if (no_digits) {
        return false;
    }

    for (int i {1}; i < s.size(); ++i) {
        if (!isdigit(s[i]) && s[i] != '.') {
            return false;
        }
        if (s[i] == '.') {
            ++number_of_dots;
            if (number_of_dots > 1) {
                return false;
            }
        }
    }
    return true;
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

            if (this->s[i] != '-' && this->s[i] != '+') {
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

            if (a.s[i] != '-' && a.s[i] != '+') {
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
    else
    {
        BigReal gr , sm;
        if(this->s > a.s)
            gr.s = this->s ,
                    sm.s = a.s;
        else
            gr.s = a.s,
                    sm.s = this->s;
        char sign = gr.s.front();
        if(gr.s.front() == '-' || gr.s.front() == '+')
            gr.s.erase(gr.s.begin());
        if(sm.s.front() == '-' || sm.s.front() == '+')
            sm.s.erase(sm.s.begin());

        BigReal subtr =  gr - sm;
        if(sign == '-')
            ans.s = "-";
        ans.s += subtr.s;

    }
    return ans;
}

BigReal BigReal::operator-(BigReal &a) {
    BigReal result;
    result.setNum("");

    if (this->isNeg() && !a.isNeg()) {
        BigReal temp;
        temp.setNum("");
        temp.s.push_back('-');
        for (int i{0}; i < a.s.size(); ++i) {
            temp.s.push_back(a.s[i]);
        }

        result = *this + temp;
        return result;
    } else if (!this->isNeg() && a.isNeg()) {
        BigReal temp;
        temp.setNum("");

        for (int i{1}; i < a.s.size(); ++i) {
            temp.s.push_back(a.s[i]);
        }

        result = *this + temp;
        return result;
    }

    int i{0};
    int j{0};
    string integer1{""};
    string integer2{""};
    string fraction1{""};
    string fraction2{""};

    for (; this->s[i] != '.' && i < this->s.size(); ++i) {
        integer1.push_back(this->s[i]);
    }

    ++i;

    for (; i < this->s.size(); ++i) {
        fraction1.push_back(this->s[i]);
    }

    for (; a.s[j] != '.' && j < a.s.size(); ++j) {
        integer2.push_back(a.s[j]);
    }

    ++j;

    for (; j < a.s.size(); ++j) {
        fraction2.push_back(a.s[j]);
    }

    if (*this > a) {
        if (!this->isNeg() && !a.isNeg()) {
            // Dealing with integer part
            string integer_result = "";
            string fraction_result = "";
            int n1 = integer1.length();
            int n2 = integer2.length();

            reverse(integer1.begin(), integer1.end());
            reverse(integer2.begin(), integer2.end());

            int carry = 0;

            for (int i = 0; i < n2; ++i) {
                int sub = ((integer1[i] - '0') - (integer2[i] - '0') - carry);

                // If subtraction is less than zero
                // we add then we add 10 into sub and
                // take carry as 1 for calculating next step
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                } else {
                    carry = 0;
                }

                integer_result.push_back(sub + '0');
            }

            // subtract remaining digits of number of greater size
            for (int i = n2; i < n1; ++i) {
                int sub = ((integer1[i] - '0') - carry);

                // if the sub value is -ve, then make it positive
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                } else {
                    carry = 0;
                }

                integer_result.push_back(sub + '0');
            }

            // reverse resultant string
            reverse(integer_result.begin(), integer_result.end());

            bool allZeros {true};
            for (int i {0}; i < integer_result.size(); ++i) {
                if (integer_result[i] != '0') {
                    allZeros = false;
                    break;
                }
            }

            if (allZeros) {
                integer_result.clear();
                integer_result.push_back('0');
            }

            if (compare_fraction(fraction1, fraction2)) {
                // Dealing with fraction part

                int n1 = fraction1.length();
                int n2 = fraction2.length();

                for (int i {0}; i < n2 - n1; ++i) {
                    fraction1.push_back('0');
                }

                for (int i {0}; i < n1 - n2; ++i) {
                    fraction2.push_back('0');
                }


                reverse(fraction1.begin(), fraction1.end());
                reverse(fraction2.begin(), fraction2.end());

                int carry = 0;

                for (int i = 0; i < n2; ++i) {
                    int sub = ((fraction1[i] - '0') - (fraction2[i] - '0') - carry);

                    // If subtraction is less than zero
                    // we add then we add 10 into sub and
                    // take carry as 1 for calculating next step
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }

                    fraction_result.push_back(sub + '0');
                }

                // subtract remaining digits of number of greater size
                for (int i = n2; i < n1; ++i) {
                    int sub = ((fraction1[i] - '0') - carry);

                    // if the sub value is -ve, then make it positive
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    fraction_result.push_back(sub + '0');
                }
                // reverse resultant string
                reverse(fraction_result.begin(), fraction_result.end());
            } else {
                string integer_result3 = "";

                int f1 = fraction1.size();
                int f2 = fraction2.size();

                for (int i {0}; i < f2 - f1; ++i) {
                    fraction1.push_back('0');
                }

                for (int i {0}; i < f1 - f2; ++i) {
                    fraction2.push_back('0');
                }

                int n3 = integer_result.length();

                reverse(integer_result.begin(), integer_result.end());

                int carry = 0;

                int sub = ((integer_result[0] - '0') - 1 - carry);

                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                } else {
                    carry = 0;
                }

                integer_result3.push_back(sub + '0');

                for (int i = 1; i < n3; ++i) {
                    int sub = ((integer_result[i] - '0') - carry);

                    // if the sub value is -ve, then make it positive
                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }

                    integer_result3.push_back(sub + '0');
                }

                // reverse resultant string
                integer_result.clear();
                reverse(integer_result3.begin(), integer_result3.end());

                for (int i {0}; i < integer_result3.size(); ++i) {
                    integer_result.push_back(integer_result3[i]);
                }

                bool allZeros {true};
                for (int i {0}; i < integer_result.size(); ++i) {
                    if (integer_result[i] != '0') {
                        allZeros = false;
                        break;
                    }
                }

                if (allZeros) {
                    integer_result.clear();
                    integer_result.push_back('0');
                }

                string fraction11 {"1"};
                string fraction22 {""};
                string fraction33 {""};

                for (int i {0}; i < fraction1.size(); ++i) {
                    fraction11.push_back(fraction1[i]);
                }

                for (int i {0}; i < fraction2.size(); ++i) {
                    fraction22.push_back(fraction2[i]);
                }


                int n1 = fraction11.length();
                int n2 = fraction22.length();

                reverse(fraction11.begin(), fraction11.end());
                reverse(fraction22.begin(), fraction22.end());

                carry = 0;

                for (int i = 0; i < n2; ++i) {
                    int sub = ((fraction11[i] - '0') - (fraction22[i] - '0') - carry);


                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }

                    fraction33.push_back(sub + '0');
                }


                for (int i = n2; i < n1; ++i) {
                    int sub = ((fraction11[i] - '0') - carry);


                    if (sub < 0) {
                        sub = sub + 10;
                        carry = 1;
                    } else {
                        carry = 0;
                    }

                    fraction33.push_back(sub + '0');
                }

                fraction_result.clear();
                reverse(fraction33.begin(), fraction33.end());

                if (fraction33.size() > fraction1.size() || fraction33.size() > fraction2.size()) {
                    string temp = fraction33;
                    fraction33.clear();
                    for (int i {1}; i < temp.size(); ++i) {
                        fraction33.push_back(temp[i]);
                    }
                }

                for (int i {0}; i < fraction33.size(); ++i) {
                    fraction_result.push_back(fraction33[i]);
                }
            }

            int w {0};
            if (integer_result.size() == 0) {
                while (integer_result[w] == '0') {
                    ++w;
                    if (w >= integer_result.size() || integer_result[w] != '0') {
                        break;
                    } else {
                        ++w;
                    }
                }
            }

            if (integer_result.size() == 0) {
                result.s.push_back('0');
            } else {
                for (; w < integer_result.size(); ++w) {
                    result.s.push_back(integer_result[w]);
                }
            }

            if (fraction_result.size() > 0) {
                result.s.push_back('.');
            }

            int fraction_result_size = fraction_result.size();

            int i = fraction_result_size - 1;


            while (i >= 0 && fraction_result[i] == '0') {
                fraction_result.pop_back();
                --i;
            }

            for (int i {0}; i < fraction_result.size(); ++i) {
                result.s.push_back(fraction_result[i]);
            }

            return result;

        } else if (this->isNeg() && a.isNeg()) {
            BigReal term1;
            BigReal term2;

            term1.setNum("");
            term2.setNum("");

            for (int i {1}; i < a.s.size(); ++i) {
                term1.s.push_back(a.s[i]);;
            }

            for (int i {1}; i < this->s.size(); ++i) {
                term2.s.push_back(this->s[i]);;
            }

            result = (term1 - term2);
            return result;
        }
    } else if (*this < a) {
        if (!this->isNeg() && !a.isNeg()) {
            result.s.push_back('-');

            BigReal temp;
            temp.setNum("");

            temp = (a - *this);

            for (int i {0}; i < temp.s.size(); ++i) {
                result.s.push_back(temp.s[i]);
            }
            return result;
        } else if (this->isNeg() && a.isNeg()) {
            result.s.push_back('-');
            BigReal term1;
            BigReal term2;
            BigReal temp;

            term1.setNum("");
            term2.setNum("");
            temp.setNum("");

            for (int i {1}; i < this->s.size(); ++i) {
                term1.s.push_back(this->s[i]);;
            }

            for (int i {1}; i < a.s.size(); ++i) {
                term2.s.push_back(a.s[i]);;
            }

            temp = (term1 - term2);
            for (int i {0}; i < temp.s.size(); ++i) {
                result.s.push_back(temp.s[i]);
            }
            return result;
        }
    } else {
        result.setNum("0.0");
        return result;
    }
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
    for(auto i : a.s)
        if(i != '+')cout<<i;
    return out;
}

void BigReal::setNum(string s) {
    this->s = s;
}

bool compare_fraction(string s1, string s2) {
    int n1 = s1.size();
    int n2 = s2.size();

    for (int i {0}; i < n2 - n1; ++i) {
        s1.push_back('0');
    }

    for (int i {0}; i < n1 - n2; ++i) {
        s2.push_back('0');
    }
    for (int i {0}; i < s1.size() && i < s2.size(); ++i) {
        if (s1[i] > s2[i]) {
            return true;
        } else if (s1[i] < s2[i]) {
            return false;
        }
    }
    return true;
}


string BigReal::getNum() const {
    return this->s;
}
