#include <iostream>
using namespace std;


bool isprime[100000];
int main(){
int n;
cin >> n;

for(int i=2;i<100000;++i)
  isprime[i]=1;

int count_=0;
for (int i=2;i<100000;++i){
if(isprime[i]){
++count_;
if(count_ == n){
    cout << i; return 0;
}
for (int j= i*i;j<100000;j+=i)
isprime[j]=0;
}
}
cout << count_;
}
