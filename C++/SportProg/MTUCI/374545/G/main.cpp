/// https://codeforces.com/gym/374545/problem/G

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{

    int a[4];
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    std::sort(a,a+4);
    if (a[0] + a[2] == a[1] + a[3] ){cout << "YES"; return 0;}
    if (a[0] + a[3] == a[1] + a[2] ){cout << "YES"; return 0;}
    if (a[0] + a[1] + a[2] == a[3] ){cout << "YES"; return 0;}
    cout << "NO";
    return 0;
}
