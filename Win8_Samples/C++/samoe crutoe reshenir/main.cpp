#include <iostream>

using namespace std;

int main()
{
    int a,b,c,d,e,f;
    char t,t1,t2;

    cin >> t >> b >> t1 >> d >> t2 >> f;
    a = t - 'A' + 1;
    c = t1 - 'A' + 1;
    e = t2 - 'A' + 1;
    cout << (a+b+c+d+e+f+1) % 10 + 1;
    return 0;
}
