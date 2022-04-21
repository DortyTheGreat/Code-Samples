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

    freopen ("input.txt","r",stdin);

    #endif // file_read
    AppBuild();

    BigUnsigned a(""),b,c;

    cin >> a >> b;

    cout << a << " " << b << endl;


    //cin >> a;
    //for(int i = 0;i<1000;++i){
    //    c = k_mul(a,a);
    //}

    ///a = k_mul(a,b);

    //a += 1;
    //fout << c << " " << a - b*c;

    return 0;
}



