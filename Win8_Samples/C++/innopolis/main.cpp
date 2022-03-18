#include <iostream>

using namespace std;

int main()
{
    char a,c;
    int b,d;
    cin >> a >> b >> c >> d;

    int dx,dy;
    dx = abs(a - c);
    dy = abs(b - d);

    cout << min(dx,dy) << " "<< max(dx,dy) ;

    return 0;
}
