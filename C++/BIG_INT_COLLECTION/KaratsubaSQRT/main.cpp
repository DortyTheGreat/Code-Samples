//
//  Main.cpp
//
//  Created by Qingqing Zhou on June 29, 2019
//

/*==================================================
1. Create a class for Karatsuba Multiplication
2. Create a class for Division
3. Create a class for Square Root
4. In main(), calculate n digits precision of sqrt(a)
5. Let user to enter the n and a from console
6. Because n can be longer than 64-bits capability,
   use string to represent the number
==================================================== */


// header files
#include <iostream>
#include "Karatsuba.cpp"
#include "Division.cpp"
#include "SqrtNewton.h"
#include "SqrtNewton.cpp"

using namespace std;

int main()
{


    Karatsuba rrr;

    cout << rrr.Subtraction("123", "456") << endl;


    std::cout<< "Newton Method - Qingqing Zhou \n\n";

    //// ============ Multiplication ========================================
    // get numbers from user
    std::string lhs{}, rhs{};

    cin >> lhs;

    Division dv;

    cout << dv.Reciprocal(lhs,100);

    std::string precision;
    // ============ Square Root ========================================
    std::cout << "Please give the number : ";
    std::cin >> lhs;
    std::cout << "\nPlease give the Precision : ";
    std::cin >> precision;

    // Sqrt using Newton
    std::cout << "\n\nSquare Root using Newton Method : \n";
    SqrtNewton sqrt{};
    std::cout << "sqrt(" << lhs << ") = " << sqrt.Sqrt(lhs, std::atoi(precision.c_str())) << std::endl;
    std::cout << "\n===================================================\n\n";
}
