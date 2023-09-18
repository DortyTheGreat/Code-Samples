#include <iostream>

using namespace std;



long double memo[10000];

long double p;
/// 10 0.400000

long double f(int n, long double multi){

    if (multi < 1e-9) return 0;
    if (n == 0) return multi;
    if (n >= 100) return 0;
    ///if (memo[n] >= 0) return memo[n];
    return /*memo[n] =*/ (f(n+3, multi*p) + f(n-1, multi*(1 - p)));
}

int main()
{
    int n;
    cin >> n;

    cin >> p;

    for(int i = 0; i < 10000; ++i){
        memo[i] = -1;
    }

    cout << f(n, 1);

    return 0;
}
