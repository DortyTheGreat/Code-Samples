#include <iostream>
#include <cmath>
using namespace std;

typedef   uint64_t    u64;
/// 10 -> 317
int main()
{
    u64 r;
    cin >> r;
    u64 ans = 0;

    u64 sr = r * r;
    u64 incr = r;

    u64 limit = sqrtl(2)/2 * r;

    for(u64 i = 1; i < limit + 1; ++i){
        while(incr*incr > sr - i * i)
            --incr;
        ///cout << i << endl;

        ans       += incr;
        cout << incr << " " << ans << endl;
    }

    cout << ans << endl;
    ans -= limit*(limit+1)/2;

    ///cout << ans;

    cout << endl << ans*8 + r*4 + 1 + limit*4;


    return 0;
}
