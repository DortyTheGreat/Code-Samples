//#pragma GCC optimize("fast-math")

#include <iostream>
#include <iomanip>

using namespace std;

#include <algorithm>

#include "../DortyLibs/OperatorBigInt.h"
#include "../DortyLibs/DortyBuild.h"

#include <fstream>



using namespace std;

int main()
{
    BigInt a,b,c;
    cin >> a >> b;
    c = a * b;
    cout << c << endl;
    /*
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    AppBuild();
    BigInt a = 1000;
    BigInt b = 999;
    BigInt c,d;


    fin >> a;

    b = a;
    a._sqrt();



    fout << a; //endl << d;

    a._mult(a);
    b._subtract(a);
    fout << endl << b;


    ///cout << a << endl;

    //cout << r << endl;


    ///cout << counter << endl;
    return 0;
    */
}
