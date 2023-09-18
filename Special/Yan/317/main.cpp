#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int64_t n;
    cin >> n;
    int64_t s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    int64_t T1=0, T2=0, T3=0;

    for(int64_t i = 1; i <= n; ++i){
        T1 += i;
        T2 += i*i;
        T3 += i*i*i;
    }

    T1 = T1 - s1;
    T2 = T2 - s2;
    T3 = T3 - s3;

    for(int64_t i = 1; i <= n; ++i){
        int64_t v2 = floor(sqrt(2*T2 - T1*T1 + 2*i*T1 - 3*i*i)) / 2;
        int64_t v3 = floor(sqrt(2*T2 - T1*T1 + 2*i*T1 - 3*i*i)) / 2;
        v3 *= (-1);

        v2 += T1/2;
        v3 += T1/2;

        v2 -= i/2;
        v3 -= i/2;


        if (T1 == (i+v2+v3) && T2 == (i*i+v2*v2+v3*v3) && T3 == (i*i*i+v2*v2*v2+v3*v3*v3)){
            cout << i << " " << v2 << " " << v3 << endl;
            return 0;
        }
    }

    return 0;
}
