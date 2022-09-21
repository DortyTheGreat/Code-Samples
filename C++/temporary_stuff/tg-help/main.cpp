#include <iostream>
using namespace std;



int main(){

    int t;
    cin >> t;

    bool isprime[1000000];

    while(t--){

        long long n, m;
        cin >> n >> m;

        for(long long i=0;i<1000000;++i)
          isprime[i]=1;


        for (long long i=n;i<=m;++i){
            if (i == 1){continue;}

            if(isprime[i - n]){

                cout << i << endl;

                for (long long j= i*i;j<1000000;j+=i)
                    isprime[j - n]=0;
            }
        }

    }
}
