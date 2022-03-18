#include <iostream>
#include <cmath>
using namespace std;

int main()
{

    bool isprime[1000000];



for(long long i=2;i<1000000;++i)
  isprime[i]=1;

long long count_=0;
for (long long i=2;i<1000000;++i){
if(isprime[i]){
++count_;

for (long long j= i*i;j<1000000;j+=i)
isprime[j]=0;
}
}

int GEN=1000000;


int AMOUNT=100;

int START=1000;

double NEGA_=1;



int primes[10000]; int h=0;
for(int i=0;i<GEN;i++){
    if(isprime[i]){
        primes[h]=i;h++;
    }
}





    for(int i=START;i<START+AMOUNT;i++){
            double num1=log((log(log(i)) + 1) * i / NEGA_)*(i);
            double num2=primes[i-1];
        cout << i<<" " <<(int)(num1) << " " << num2 << " " <<(int)((num1/num2)*1000) <<  endl;;

    }
}
