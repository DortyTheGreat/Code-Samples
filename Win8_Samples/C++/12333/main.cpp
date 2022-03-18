#include <iostream>
using namespace std;
int main()
{
int n, s;
n = 1024;
    cin >> s;
    while(s >= 5) {
        s = s - 5;
        n = n / 2;
    }
    cout << n;
    return 0;
}
