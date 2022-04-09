//
//  Karatsuba.cpp
//
//  Created by Qingqing Zhou on June 29, 2019
//

#include <iostream>
#include <sstream>
#include <string>
#include "Karatsuba.h"

int Karatsuba::MakeEqualLength(std::string &str1, std::string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0; i < len2 - len1; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0; i < len1 - len2; i++)
            str2 = '0' + str2;
    }
    return len1;
}

std::string Karatsuba::Add(std::string lhs, std::string rhs)
{
    std::string result{};  // To store the sum bits

    // make the lengths same before adding
    int length = MakeEqualLength(lhs, rhs);
    int carry = 0;  // Initialize carry

    // Add all bits one by one
    for (int i = length - 1; i >= 0; i--)
    {
        int lhs_digit = lhs.at(i) - '0';
        int rhs_digit = rhs.at(i) - '0';

        int sum{ lhs_digit + rhs_digit + carry };

        result = (char)(sum % 10 + '0') + result;

        carry = sum / 10;
    }

    // if overflow, then add a leading 1
    if (carry)
    {
        result = '1' + result;
    }

    return result;
}

std::string Karatsuba::Subtraction(std::string lhs, std::string rhs)
{

    int length = MakeEqualLength(lhs, rhs);
    int diff;
    std::string result{};

    for (int i = length - 1; i >= 0; i--)
    {
        diff = (lhs[i] - '0') - (rhs[i] - '0');
        if (diff >= 0)
        {
            result = std::to_string(diff) + result;
        }
        else
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (lhs[j] == '0')
                {
                    lhs[j] = '9';
                }
                else
                {
                    lhs[j] -= 1;
                    break;
                }
            }
            result = std::to_string(diff + 10) + result;
        }
    }

    return result;
}

std::string Karatsuba::Shift(std::string str, int stepnum)
{
    std::string shifted{ str };
    for (int i = 0; i < stepnum; i++)
        shifted = shifted + '0';
    return shifted;
}

std::string Karatsuba::multiply(std::string lhs, std::string rhs)
{
    return RemoveLeadingZero(MultiplyRecur(lhs, rhs));
}

std::string Karatsuba::MultiplyRecur(std::string X, std::string Y)
{
    int n = MakeEqualLength(X, Y);

    if (n == 1) return std::to_string(std::stoi(Y) * std::stoi(X));

    int fh = n / 2;   // First half of string
    int sh = (n - fh); // Second half of string, ceil(n/2)

    // Find the first half and second half of first string.
    std::string X1 = X.substr(0, fh);    // high half
    std::string X0 = X.substr(fh, sh);   // low half

    // Find the first half and second half of second string
    std::string Y1 = Y.substr(0, fh);
    std::string Y0 = Y.substr(fh, sh);

    // Recursively calculate the three products of inputs of size n/2
    // Z0 = X0 * Y0
    std::string Z0 = MultiplyRecur(X0, Y0);
    // Z2 = X1 * Y1
    std::string Z2 = MultiplyRecur(X1, Y1);
    // Z1 = (X0 + X1)(Y0 + Y1) - Z0 - Z2
    std::string Z1 = MultiplyRecur(Add(X0, X1), Add(Y0, Y1));
    Z1 = Subtraction(Z1, Add(Z0, Z2));

    // return added string version
    // Z = Z2 * (10^(low half digits * 2)) + Z1 * (10^(low half digit)) + Z0
    return Add(Add(Shift(Z2, sh*2), Z0), Shift(Z1, sh));
}

std::string Karatsuba::RemoveLeadingZero(std::string str)
{
    if (str.length() < 2)
    {
        return str;
    }

    while (str[0] == '0' && str.length() > 1)
    {
        str = str.substr(1, str.length() - 1);
    }

    return str;
}
