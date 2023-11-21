#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

typedef   uint64_t    u64;
/// 10 -> 317
int main()
{
    ifstream fin("input.txt");
    u64 r;
    fin >> r;
    u64 ans = 0;

    u64 sr = r * r;
    u64 incr = r;

    u64 limit = sqrtl(2)/2 * r;

    for(u64 i = 1; i < limit + 1; ++i){
        if(incr*incr > sr - i * i)
            --incr;
        ///cout << i << endl;
        ans += incr;
    }


    ans -= limit*(limit+1)/2;

    ///cout << ans;

    cout << ans*8 + r*4 + 1 + limit*4;


    return 0;
}
