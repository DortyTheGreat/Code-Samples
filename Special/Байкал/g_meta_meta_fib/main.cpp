#include <iostream>
#include <iomanip>
#define int long long


const int count_ = 100 * 1000 * 1000;

/// 100 ->     135
/// 1000 ->    2225
/// 10000 ->   29810 (2.9810)
/// 100k ->    382521 (
/// 1m ->      4692509
/// 10m ->     54717329
/// 100m ->    632223590

/// *1k -> +2.4970259 to coeff

/// 10^(3/2)

int meme_[count_];
int meta_fib(int n){
    if (n == 1) return 1;
    if (n == 2) return 1;
    if (meme_[n] != -1337) return meme_[n];
    return meme_[n] = (meta_fib(n - meta_fib(n-1)) + meta_fib(n-1 - meta_fib(n-2)));
}

using namespace std;

signed main()
{

    for(int meme = 0; meme < count_; ++meme){
        meme_[meme] = -1337;
    }

    /// 100 -> 135
    /// 1000 -> 2225
    /// 3000 -> 7677 diff (2.559)
    /// 4000 -> 10873 (2.71)
    /// 10000 -> 29810 (2.9810)
    for(int i = 1;i < count_; ++i){
        //cout << setw(5) << meta_fib(i) << " ";
    }

    cout << endl;


    cout << endl;


    cout << endl;


    for(int i = 1;i < count_; ++i){
        int sum = 0;

        //cout << setw(5) <<i << " ";
    }
    cout << endl;

    for(int i = count_ - 1;i < count_; ++i){
        int sum = 0;
        for(int j = 1;j <= i; ++j){
            sum += meta_fib(j) - (j)/2;
        }
        cout  << setw(5) << sum << " ";
    }
    cout << endl;

    return 0;
}
