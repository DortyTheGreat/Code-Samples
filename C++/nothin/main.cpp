#pragma GCC target ("avx2") /// ����� ��� �����
#pragma GCC optimization ("O3") /// �������� �������� ��������
#pragma GCC optimization ("unroll-loops")

#include "../DortyLibs/AdvancedStream.h"

#include <cmath>
using namespace std;
#include <stdio.h>
#include "../DortyLibs/BigIntLib.h"

#include "../DortyLibs/DortyBuild.h"


#define file_read 1



int main()
{

    #if file_read

    freopen ("input.txt","r",stdin);

    #endif // file_read
    AppBuild();

    BigInt a,b,c;

    cin >> a;
    for(int i = 0;i<1000;++i){
        c = k_mul(a,a);
    }

    ///a = k_mul(a,b);

    //a += 1;
    //fout << c << " " << a - b*c;

    return 0;
}



