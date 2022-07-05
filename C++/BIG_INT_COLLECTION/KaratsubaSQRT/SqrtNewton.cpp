//
//  SqrtNewton.cpp
//
//  Created by Qingqing Zhou on June 29, 2019
//
//  Use Newton method to calculate squre root
//  with higher precision for more than 64 bits
//

#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <cmath>
#include "Karatsuba.h"
#include "Division.h"
#include "SqrtNewton.h"

#define DEBUG_SQRT

void SqrtNewton::PrintDetails(int i, std::string text)
{
#ifdef DEBUG_SQRT
    std::cout << "Division: x[" << i << "] = " << text << std::endl;
#endif
}


/// "123", 2] ["1234", ceil(size/2) + 1]
std::string SqrtNewton::Sqrt(std::string num, int precision)
{
    // x(i+1) = ( x(i) + a / x(i) ) / 2

    // Initial guess
    std::string x0{};
    if (num.length() == 1)
    {
        x0 = std::to_string(atoi(num.c_str()) / 2);
        x0.append(precision, '0');
    }
    else
    {
        x0 = (num.length() % 2) ? "2" : "7";
        //std::string x0{ std::to_string(atoi(num.c_str()) / 2) };
        x0.append((num.length() - 1) / 2 + precision, '0');
    }
    PrintDetails(0, x0);

    Division div{};
    Karatsuba kar{};

    // Do the interation to fullfil the precision
    int end{ int(std::log2(precision)) + 1 };
    for (int i = 0; i < end; i++)
    {
        // x(i) * 10^precision + a * 10^(2*precision) / x(i)
        std::string v{ div.DivInt(num, x0, 2 * precision) };
        x0 = div.Div(kar.Add(x0, v), "2", precision);
        PrintDetails(i + 1, x0);
    }

    size_t i_cnt{ x0.length() - precision };
    return x0.substr(0, i_cnt) + '.' + x0.substr(i_cnt, precision - i_cnt);
}
