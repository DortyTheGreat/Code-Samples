#include <iostream>
#include "BigIntegerWrapper.cpp"

using namespace std;

int main()
{
    BigInteger::Boot();

    BigInteger two("2");
    BigInteger result = two.Pow(20);
    cout << result.ToString(2) << endl; // output string in Base 2

    return 0;
} // end main
