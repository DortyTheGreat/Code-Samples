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
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    AppBuild();

    BigInt a,b;

    BigInt * c;

    fin >> a >> b;
    c = k_mul(&a,&b);
    fout << *c << endl;


    return 0;
}
