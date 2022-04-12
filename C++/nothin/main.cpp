#include <iostream>
#include "../DortyLibs/DortyGraph.h"
#include "../DortyLibs/DortyBuild.h"
#include "../DortyLibs/BetterVector.h"
#include "../DortyLibs/Cython.h"
#include "../DortyLibs/algo.h"
#include "../DortyLibs/OperatorBigInt.h"
#include <fstream>
#include "../DortyLibs/NewtonsSQRT.h"
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    AppBuild();
    BigInt a = 1000;
    BigInt b = 999;
    BigInt c,d;


    cin >> a;

    b = a;
    //a._sqrt();
    a = sqrt(a);


    cout << a; //endl << d;

    a *= a;
    b._subtract(a);
    cout << endl << b;


    ///cout << a << endl;

    //cout << r << endl;


    ///cout << counter << endl;
    return 0;
}

