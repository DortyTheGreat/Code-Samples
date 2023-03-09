#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long double a,b,c,d;

    int t;
    cin >> t;

    while(t--){
        cin >> a >> b >> c >> d;

        long double v1 = b * logl(a);
        long double v2 = d * logl(c);

        long double small_val = powl(10,-20);

        if ( abs(v1 - v2) <  small_val){
            cout << "=" << endl;
        }else{
            if (v1 > v2){
                cout << ">" << endl;
            }else{
                cout << ">" << endl;
            }
        }
    }

    return 0;
}
