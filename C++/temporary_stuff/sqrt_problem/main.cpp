#include <iostream>

using namespace std;

long double const error = 1e-18;
#include <cmath>
bool isWhole(long double num){
    long double r = (num - floor(num));
    if (r > 0.5) r = 1 - r;
    if (r < error) return true;
    return false;
}
#include <iomanip>

std::pair<int, long long> solve(long double f){
    int a = 0;
    while(1){

        f -= 1;
        a++;
        long double sqr = f*f;
        if ( isWhole(sqr)  ){
                /*
            cout << a << " " << setprecision(30) << sqr;

            cout << endl;
            cout << setprecision(20) << " " <<a + sqrtl(sqr);
            */
            return {a,sqr};
        }

    }
}

int main()
{
    int m = -1;

    int I = 100028702 + 100000;
    int J = 200031425;

    for(int i = I; i < I + 1000000; ++i){
        for(int j = J; j < J + 3; ++j){
            long double f = i + sqrtl(j);
            auto res = solve(f);
            if (res.first > m){
                m = res.first;
                cout << res.first << " ";
                cout << " " <<  i << " " << j << endl;
                cout << endl;
            }
        }
    }


    cout << "Hello world!" << endl;
    return 0;
}
