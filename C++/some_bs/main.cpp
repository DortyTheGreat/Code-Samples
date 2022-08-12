#include <iostream>
#include "../DortyLibs/DortyBuild.h"

#include "../DortyLibs/DinBigLib.h"
using namespace std;



int main()
{
    AppBuild();
    string a,b;
    cin >> a >> b;
    bool flag = 0;
    if (a[0] == '-'){flag ^= 1;a = a.substr(1,a.size() - 1);}
    if (b[0] == '-'){flag ^= 1;b = b.substr(1,b.size() - 1);}

    BigUnsigned c(a), d(b);


    BigUnsigned ans = karatsuba(c,d);
    if (ans == BigUnsigned()){
        cout << "0";
        return 0;
    }

    if (flag){cout << '-';}
    cout << karatsuba(c,d) << endl;

}
