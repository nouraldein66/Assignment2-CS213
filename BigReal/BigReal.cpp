// File: BigReal.cpp
// Purpose: Making a class for big real numbers that ordinary C++ data types cannot handle
// Authors: Nour Aldeen, Ahmed Alaa Aldeen, Ahmed Abdelnabi
// Section: S23, S24
// ID: 20220360, 20220028, 20220027
// TA: Muhammad Talaat
// Date: 5 Nov 2023

#include "BigReal.h"

namespace br {

BigReal::BigReal(const std::string &s) {
    if (!isValid(s)) {
        throw std::invalid_argument("Invalid numeric format: " + s);
    }
    value = Decimal(s);
}

bool BigReal::isValid(const std::string &s) {
    if (s.empty()) return false;
    bool dot = false;
    size_t start = (s[0] == '+' || s[0] == '-') ? 1 : 0;
    if (start == s.size()) return false;
    for (size_t i = start; i < s.size(); ++i) {
        if (s[i] == '.') {
            if (dot) return false;
            dot = true;
        } else if (!std::isdigit(s[i])) {
            return false;
        }
    }
    for (char c : s) if (std::isdigit(c)) return true;
    return false;
}

std::string BigReal::toString() const {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

BigReal operator+(const BigReal &lhs, const BigReal &rhs) {
    return BigReal(lhs.value + rhs.value);
}
BigReal operator-(const BigReal &lhs, const BigReal &rhs) {
    return BigReal(lhs.value - rhs.value);
}
BigReal operator*(const BigReal &lhs, const BigReal &rhs) {
    return BigReal(lhs.value * rhs.value);
}
BigReal operator/(const BigReal &lhs, const BigReal &rhs) {
    if (rhs.value == 0) throw std::runtime_error("Division by zero");
    return BigReal(lhs.value / rhs.value);
}

bool operator==(const BigReal &lhs, const BigReal &rhs) { return lhs.value == rhs.value; }
bool operator!=(const BigReal &lhs, const BigReal &rhs) { return !(lhs == rhs); }
bool operator<(const BigReal &lhs, const BigReal &rhs)  { return lhs.value < rhs.value; }
bool operator<=(const BigReal &lhs, const BigReal &rhs) { return lhs.value <= rhs.value; }
bool operator>(const BigReal &lhs, const BigReal &rhs)  { return lhs.value > rhs.value; }
bool operator>=(const BigReal &lhs, const BigReal &rhs) { return lhs.value >= rhs.value; }

std::ostream &operator<<(std::ostream &os, const BigReal &r) {
    os << r.value;
    return os;
}

std::istream &operator>>(std::istream &is, BigReal &r) {
    std::string token;
    is >> token;
    if (!BigReal::isValid(token)) {
        is.setstate(std::ios::failbit);
    } else {
        r.value = Decimal(token);
    }
    return is;
}

}
