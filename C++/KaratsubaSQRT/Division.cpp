//
//  Division.cpp
//
//
//  Created by Qingqing Zhou on June 29, 2019
//
//  Using Newton method with Karatsuba multiplication
//  for precision requirements of longer than 64 bits
//

#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <cmath>
#include "Division.h"
#include "Karatsuba.h"

#define DEBUG_DIVISION

template <typename T>
std::string Division::to_string_with_precision(const T a_value, const int n)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

void Division::PrintDetails(int i, std::string text)
{
#ifdef DEBUG_DIVISION
    std::cout << "Division: x[" << i << "] = " << text << std::endl;
#endif
}

std::string Division::ShiftR(std::string str, const int R)
{
    return str.substr(0, str.length() - R);
}

std::string Division::Reciprocal(std::string num, int precision)
{
    // Initial Guess
    //int first_digit{ num.at(0) - '0' };
    //std::string x0{ "1" };
    //if (first_digit >= 5)
    //{
    //    x0 = "5";
    //}
    //else if (first_digit >= 2)
    //{
    //    x0 = "2";
    //}
    //size_t len{ (num.length() > 6) ? 6 : num.length() };

    //x0.append(len - 1, '0');

    //std::string dividend{ "1" };
    //dividend.append(len, '0');
    //// Extra condition for initial guess is
    //// x(i) < 2R/b
    //// Therefore (-1) below to make sure it's smaller
    //x0 = std::to_string(atoi(dividend.c_str()) / atoi(x0.c_str()) - 1);




    size_t len{ (num.length() > 7) ? 8 : num.length() };
    std::string x0{ num.substr(0, len) };
    std::string dividend{ "1" };
    dividend.append(len, '0');

    // Extra condition for initial guess is: x(i) < 2R/b
    x0 = std::to_string(atoi(dividend.c_str()) / atoi(x0.c_str()));
    x0.append(precision - num.length(), '0');
    PrintDetails(0, x0);

    // Do the interation to fullfil the precision
    int end{ int(std::log2(precision)) + 1 };
    for (int i = 0; i < end; i++)
    {
        x0 = Interate(num, x0, precision);
        PrintDetails(i + 1, x0);
    }

    return x0;
}

std::string Division::Interate(std::string b, std::string xi, int precision)
{
    // 2 * X(i) - b * X(i)^2 / R
    Karatsuba kar{};
    // 2 * X(i)
    std::string v1{ kar.multiply(std::to_string(2), xi) };
    // b * X(i)^2
    std::string v2{ kar.multiply(xi, xi) };
    std::string v3{ kar.multiply(b, v2) };
    // / R
    std::string v4{ ShiftR(v3, precision) };

    return kar.RemoveLeadingZero(kar.Subtraction(v1, v4));
}

std::string Division::DivInt(std::string lhs, std::string rhs, size_t precision)
{
    Karatsuba kar{};

    return kar.multiply(Reciprocal(rhs, precision), lhs);
}

std::string Division::Div(std::string lhs, std::string rhs, size_t precision)
{
    Karatsuba kar{};

    std::string value{ DivInt(lhs, rhs, precision) };

    if (precision >= value.length())
    {
        return "0";
    }
    else
    {
        return value.substr(0, value.length() - precision);
    }
}

std::string Division::DivFloat(std::string lhs, std::string rhs, size_t precision)
{
    Karatsuba kar{};

    std::string value{ DivInt(lhs, rhs, precision) };

    if (precision >= value.length())
    {
        std::string zeros(precision - value.length(), '0');
        value = zeros + value;
        return "0." + value;
    }
    else
    {
        size_t i_cnt{ value.length() - precision };
        size_t f_cnt{ precision - i_cnt };
        return f_cnt > 0 ?
                value.substr(0, i_cnt) + '.' + value.substr(i_cnt, f_cnt) :
                value.substr(0, i_cnt);
    }
}
