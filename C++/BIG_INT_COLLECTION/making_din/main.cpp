//#pragma GCC target ("avx2") /// говно для ноута
//#pragma GCC optimization ("O3") /// немножко ускоряет карацубу
//#pragma GCC optimization ("unroll-loops")

using namespace std;
#include <iostream>
#include "../../DortyLibs/DortyTime.h"


#include <cmath>

#include <stdio.h>
#include "../../DortyLibs/DinBigLib.h"

#include "../../DortyLibs/DortyBuild.h"


#define file_read 1



int main()
{

    ///cout << "here2 " << endl;
    #if file_read

    freopen ("double_10k.txt","r",stdin);

    #endif // file_read
    AppBuild();




    cout << "here" << endl;
    BigUnsigned a,b,c;

    cin >> a;
    b = a;
    ///cout << "var c : " << c << endl;


    for(int i = 0;i<100;i++){
        c = karatsuba(a,b);
    }

    /// 0.2 100 10kx10k





    return 0;
}



