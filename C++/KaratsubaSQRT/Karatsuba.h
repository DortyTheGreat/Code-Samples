//
//  Karatsuba.cpp
//
//  Created by Qingqing Zhou on June 29, 2019
//

#ifndef KARATSUBA_h
#define KARATSUBA_h

#include <iostream>
#include <vector>
#include <string>

class Karatsuba
{
public:
    std::string multiply(std::string lhs, std::string rhs);
    std::string Subtraction(std::string lhs, std::string rhs);
    std::string RemoveLeadingZero(std::string str);
    std::string Add(std::string lhs, std::string rhs);

private:
    int MakeEqualLength(std::string& str1, std::string& str2);

    std::string MultiplyRecur(std::string X, std::string Y);
    std::string Shift(std::string str, const int stepnum);
};

#endif /* KARATSUBA_h */