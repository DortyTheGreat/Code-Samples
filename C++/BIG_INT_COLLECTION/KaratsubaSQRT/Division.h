//
//  Division.h
//
//
//  Created by Qingqing Zhou on June 29, 2019
//
//  Using Newton method with Karatsuba multiplication
//  for precision requirements of longer than 64 bits
//

#ifndef DIVISION_H
#define DIVISION_H

#include <iostream>
#include <vector>
#include <string>

class Division
{
public:

    // Calculate 1/num and giving precision digits

    // @Param precision: 10^precision, # of digits
    std::string Reciprocal(std::string num, int precision);

    std::string Div(std::string lhs, std::string rhs, size_t precision);
    std::string DivInt(std::string lhs, std::string rhs, size_t precision);
    std::string DivFloat(std::string lhs, std::string rhs, size_t precision);

private:
    template <typename T>
    std::string to_string_with_precision(const T a_value, const int n = 6);
    std::string ShiftR(std::string str, const int R);
    std::string Interate(std::string b, std::string xi, int precision);
    void PrintDetails(int i, std::string text);
};

#endif /* DIVISION_H */