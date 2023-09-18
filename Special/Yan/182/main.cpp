#include <iostream>

using namespace std;

#include <vector>
#include <cmath>

bool IsSquare(long long number){
    return (int)(sqrt( abs(number))) == sqrt( abs(number));
}

vector<uint64_t> all_divisers(uint64_t number){
    vector<uint64_t> ans;
    int sqrt_= sqrt( number );
    for(int i=1;i<=sqrt_;i++){
        if(number%i==0){ans.push_back(i);}
    }
    for(int counter = (ans.size()) - (IsSquare(number));counter !=0;ans.push_back(number / (ans[--counter]))){}
    return ans;
}

template<typename T>
inline T gcd(T a, T b)
{
    while(a %=b) if (!(b %= a)) return a;
    return b;
}

int main()
{
    uint64_t x,y;
    cin >> x >> y;
    if (y % x != 0){
        cout << 0 << endl; return 0;
    }

    y /= x;
    auto vc = all_divisers(y);

    int ans = 0;
    for(auto elem : vc){
        if (gcd(elem,y/elem) == 1){
            ans++;
        }
    }

    cout << ans;

    return 0;
}
