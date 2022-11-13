#include <iostream>
#define int long long
using namespace std;

int b;
int n;



/// Сколько нужно ещё чисел?

const int buff_sz = 100 * 10000;

int buffer[buff_sz];
int f(int n){
    if (n == 0) return 0;
    if (n < buff_sz && buffer[n] != -1) return buffer[n];

    for(int k = 1, p = 2; p <= n; ++k, p = (k)*(k+1)){

    }


}

signed main()
{

    int n;
    cin >> n;
    cout << f(n);

    return 0;
}
