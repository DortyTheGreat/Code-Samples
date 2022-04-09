//
//  SqrtNewton.h
//
//  Created by Qingqing Zhou on June 29, 2019
//
//  Use Newton method to calculate squre root
//  with higher precision for more than 64 bits
//

#ifndef SQRT_NEWTON_H
#define SQRT_NEWTON_H

#include <iostream>
#include <vector>
#include <string>

class SqrtNewton
{
public:

    // Calculate 1/num and giving precision digits
    std::string Sqrt(std::string num, int precision);

private:
    void PrintDetails(int i, std::string text);
};

#endif /* SQRT_NEWTON_H */