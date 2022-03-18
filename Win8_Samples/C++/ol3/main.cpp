#include <iostream>

using namespace std;

int main()
{
    int a;
    cin >> a;

    for(int i =0;i<a-1;i++){
        int t1,t2;
        cin>> t1 >> t2;

    }

    long long ans = 1;
    long long module = 1000000007;

    for(int i =0;i<a-1;i++){
        ans = (ans * 2) % module;
    }

    ans = (ans * a) % module;

    long long rest = a-1;

    rest = (rest * rest) % module;

    rest = (rest * a) % module;

    ans = (ans + rest) % module;


    cout << ans;

    return 0;
}
