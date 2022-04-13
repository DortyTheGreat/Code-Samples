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

    BigInt a,b,c;
    fin >> a >> b;
    c = a * b;
    fout << c << endl;


    return 0;
}
