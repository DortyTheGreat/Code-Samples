#include <iostream>

using namespace std;

int main()
{
    for(int i = -10000;i<100000;i++){
        int M = i;
        int C = 8;
        int R = 0;
        int N = 1;
        int T = 0;

        cycle:

        if (M != 0){
            T = 0;
            cycle2:

            if (M >= C){
                T = T+1;
                M = M-C;
                goto cycle2;

            }else{
                R = R+M*N;
                N = N*10;
                M = T;
                goto cycle;
            }

        }else{
            if (R == 31077){
                cout << i <<" " <<R <<endl;
            }
        }

    }
    return 0;
}
