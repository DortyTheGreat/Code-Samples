#include <iostream>
#include <KulAi.h>
using namespace std;

int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b)
{
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

int main()
{
    int n,s;

    int NUM = 1;

    cin >> n >> s;

    for(int i = 0 ;i<n;i++){
        int temp;
        cin >> temp;

        NUM = lcm(NUM,temp);
    }

    int ans = (NUM + s)% 7;

    if (ans == 0){ans = 7;}

    cout << ans;

}
