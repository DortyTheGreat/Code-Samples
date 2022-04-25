//#pragma GCC target ("avx2") /// говно для ноута
//#pragma GCC optimization ("O3") /// немножко ускоряет карацубу
//#pragma GCC optimization ("unroll-loops")

#include "../DortyLibs/AdvancedStream.h"

#include <cmath>
using namespace std;
#include <stdio.h>
#include "../DortyLibs/DinBigLib.h"

#include "../DortyLibs/DortyBuild.h"


#define file_read 1



int main()
{

    #if file_read

    ///freopen ("million.txt","r",stdin);

    #endif // file_read
    AppBuild();

    BigUnsigned a,b,c;

    cin >> a >> b;

    /// 100k memcpy of 100k ints (aka 1 million decimal places) in 5 s
    /// -> 100 allocs in 5 ms
    /// -> 1 alloc in 0.05 ms (INSANELY QUICKLY!)
    for(int i = 0;i<1;++i){

        ///b = a;
        //CONT_TYPE * d = new CONT_TYPE[100000];
        ///cout << karatsuba(a,b);
        /// Почему-то... ПОЧЕМУ только половина знаков будет значима..
        cout << Reciprocal(a,4) << endl;
        BigUnsigned r =Reciprocal(b,4);
        cout << "r  :" << r <<endl;
        ///cout << karatsuba(a,r) << endl;


        ///x_mul(a,a);

    }






    return 0;
}



