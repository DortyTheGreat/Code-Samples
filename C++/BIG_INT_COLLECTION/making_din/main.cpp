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


#define file_read 0



int main()
{

    ///cout << "here2 " << endl;
    #if file_read

    freopen ("double_10k.txt","r",stdin);

    #endif // file_read
    AppBuild();





    BigUnsigned a,b, r;

    cin >> a >> b;
    r = Reciprocal(b,1);
    cout << r << endl;
    cout << endl<< DivisionWithKnownReciprocal(a,r,(1 << 1));

    /// 0.2 100 10kx10k





    return 0;
}



