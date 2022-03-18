#include <iostream>

using namespace std;

int main()
{
    double Str,Agi;

    double Tar;
    cout << "input str: "; cin >> Str;
    cout << "input Agi: "; cin >> Agi;
    cout << "input Tarascs: "; cin >> Tar;

    double ValueS = (Str + Tar * 18.16 );
    double ValueA = (Agi + 1.5);

    double Coef = ValueS/ValueA;
    cout << "ValueA : " << ValueA << endl;
    cout << "ValueS : " << ValueS << endl;
    cout << "Coef : " <<Coef << endl;

    cout << Coef << endl;
}
