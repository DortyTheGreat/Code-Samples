#include <iostream>
using namespace std;

#include "..\DortyLibs\DortyTime.h"
//Clock MainClock;

#include "..\DortyLibs\DinBigLib.h"
#include "..\DortyLibs\DortyBuild.h"

int main()
{
    ifstream fin("123456789.txt");
    ifstream fin10("123456789_10.txt");
    ifstream fin10k("10k.txt");
    BigUnsigned num,num10,num10k, zero;

    fin10k >> num10k;
    for(int i = 0;i<1000;++i){
        num10k = num10k + zero + zero + zero + zero + zero + zero + zero + zero + zero + zero + zero + zero + zero;
    }
    cout << zero << endl;






    cout << "Hello world!" << endl;
    return 0;
}
