#include <iostream>
#include "../DortyLibs/DortyGraph.h"
#include "../DortyLibs/DortyBuild.h"
#include "../DortyLibs/BetterVector.h"
#include "../DortyLibs/Cython.h"
#include "../DortyLibs/algo.h"
#include "../DortyLibs/BigInt.h"
#include <fstream>
using namespace std;

int main()
{
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
}
