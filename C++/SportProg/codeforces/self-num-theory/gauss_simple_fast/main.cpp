#include <iostream>
#include <cmath>
using namespace std;

typedef   uint64_t    u64;
/// 10 -> 317
int main()
{
    u64 r;
    cin >> r;

    if (r == 0){
        cout << 1 << endl;
        return 0;
    }
    u64 a = (-1 * (r/sqrtl(2)) / 1 * -1);
    u64 iterpoint = 0;
    for (u64 x=a; x < r + 1; ++x){
        cout << x << endl;
        cout << floor(sqrtl(r*r-x*x)) << endl;
        cout << endl;
        iterpoint += x - floor(sqrtl(r*r-x*x));
        cout << iterpoint << endl;
    }

    cout << 4*a + 4*r*r - 8*iterpoint - 3;


    return 0;
}
