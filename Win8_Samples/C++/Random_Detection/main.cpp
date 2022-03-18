#include <iostream>

using namespace std;
#define int long long
signed main()
{
    int arraR[1000];

    for(int i=0;i<1000;i++){
        arraR[i] = 0;
    }

    int N=10000000000;

    int carret = 0;
    for(int i=0;i<N;i++){
            if(rand()%2){
                carret+=1;
            }else{
            arraR[carret]++;
            carret=0;
            }
        //cout << rand()%2 << " ";
    }
    for(int i =0;i<100;i++){
        cout << i << " : " << arraR[i] << endl;
    }

}
