#include <iostream>

using namespace std;

int f(int a, int b, int c, int d){
    return a + 2*b + 3*c + 4*d - a*a - b*b - c*c - d*d;
}

/**
1033*a*b + 1000*b*c + 1000*c*d with sum = 63
992690 30 31 1 1


1032*a*b + 1000*b*c + 1000*c*d with sum = 63
991992 1 31 30 1

*/


int main()
{
    int maxima = -1001 * 1001 * 1001;
    int minima = 1001 * 1001 * 1001;
    for(int a = -100; a < 100; ++a){
        for(int b = -100; b < 100; ++b){
            for(int c = -100; c < 100; ++c){
                for(int d = -100; d < 100; ++d){
                    if (a + b + c + d == 63){
                        int val = f(a,b,c,d);
                        if (val > maxima){
                            maxima = val;
                            cout << maxima << " " << a << " " << b << " " << c << " " << d << endl;
                        }

                        if (val < minima){
                            minima = val;
                            ///cout << minima << " " << a << " " << b << " " << c << " " << d << endl;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
