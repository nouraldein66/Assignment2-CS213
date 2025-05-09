// File: BigReal.h
// Purpose: Making a class for big real numbers that ordinary C++ data types cannot handle
// Authors: Nour Aldeen, Ahmed Alaa Aldeen, Ahmed Abdelnabi
// Section: S23, S24
// ID: 20220360, 20220028, 20220027
// TA: Muhammad Talaat
// Date: 5 Nov 2023

#ifndef BIGREAL_H
#define BIGREAL_H

#include <string>
#include <stdexcept>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace br {

using Decimal = boost::multiprecision::cpp_dec_float_50;

class BigReal {
public:
    BigReal() = default;
    explicit BigReal(const std::string &s);
    explicit BigReal(const Decimal &d) : value(d) {}

    static bool isValid(const std::string &s);

    std::string toString() const;

    friend BigReal operator+(const BigReal &lhs, const BigReal &rhs);
    friend BigReal operator-(const BigReal &lhs, const BigReal &rhs);
    friend BigReal operator*(const BigReal &lhs, const BigReal &rhs);
    friend BigReal operator/(const BigReal &lhs, const BigReal &rhs);

    friend bool operator==(const BigReal &lhs, const BigReal &rhs);
    friend bool operator!=(const BigReal &lhs, const BigReal &rhs);
    friend bool operator<(const BigReal &lhs, const BigReal &rhs);
    friend bool operator<=(const BigReal &lhs, const BigReal &rhs);
    friend bool operator>(const BigReal &lhs, const BigReal &rhs);
    friend bool operator>=(const BigReal &lhs, const BigReal &rhs);

    friend std::ostream &operator<<(std::ostream &os, const BigReal &r);
    friend std::istream &operator>>(std::istream &is, BigReal &r);

private:
    Decimal value;
};

}

#endif // BIGREAL_H
