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

    freopen ("100k.txt","r",stdin);

    #endif // file_read
    AppBuild();





    BigUnsigned a,b, r;

    cin >> a;

    for(int i =0;i<50;++i){
        karatsuba(a,a);
    }
    /// 80 ms for 100x100

    //r = Reciprocal(b,10);
    ///print(r._digits,1<<3);
    //cout << endl<< DivisionWithKnownReciprocal(a,r, b.real_size);

    /// 0.2 100 10kx10k





    return 0;
}



