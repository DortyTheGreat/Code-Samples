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

    freopen ("10_5.txt","r",stdin);

    #endif // file_read
    AppBuild();

    BigUnsigned a,b,c;

    cin >> a >> b;

    /// если я вот сюда запишу cout << a << " " << b << endl;
    /// то нихуя работать не будет, будет какой-то пиздец

    /// 100k memcpy of 100k ints (aka 1 million decimal places) in 5 s
    /// -> 100 allocs in 5 ms
    /// -> 1 alloc in 0.05 ms (INSANELY QUICKLY!)


    /// Во-первых: умножение капец какое долгое: на 10к * 5к ~= 0.1 секунда (у школьного уйдёт при 10k на 10k 0.3, как-то мало увеличивает)
    /// А ДЕЛЕНИЕ - капец какое долгое! 2 секунды при тех же параметрах

    BigUnsigned r =Reciprocal(b,intlog(2,a.real_size) + 2 ) ;
    for(int i = 0;i<2;++i){

        ///b = a;
        //CONT_TYPE * d = new CONT_TYPE[100000];
        ///cout << karatsuba(a,b);
        /// Почему-то... ПОЧЕМУ только половина знаков будет значима..
        ///cout << Reciprocal(a,4) << endl;


        ///cout << "a " << a << endl;
        ///cout << "b " << b << endl;
        ///cout << "r " <<r << endl;
        cout << a.real_size << endl;
        c= DivisionWithKnownReciprocal(a,r, b, b.real_size - 1 + a.real_size);
        cout << a.real_size << endl;
        ///cout << "b : " << b << endl;
        ///cout << b.real_size << endl;
        ///karatsuba(a,b);
        cout << "c: "<< c << endl;


        ///x_mul(a,a);

    }






    return 0;
}



