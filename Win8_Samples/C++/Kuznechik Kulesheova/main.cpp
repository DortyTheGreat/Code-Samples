#include <iostream>
#include <iomanip>
using namespace std;



//Немного оптимизации и комментариев
long long BetterMod(long long a, long long b){
if (a % b == 0){return b;}
if (a < 0){return (a % b) + b;}
return abs(a % b);
}


int main(){
long long n=5;
long long m=11;
long long a=2;
long long b=6;

cin >> a >> b >>n >> m;

if( m < n){
    swap(m,n);
    swap(a,b);
}

long long Xf = a;
long long Bf = BetterMod(b-a,m);
for(long long i=0;i<1000 * 1000 ;i++){
 long long X = Xf + i*n;
 //cout << X << " " << X%m << endl;
 if(X%m == b){cout << X; return 0;}
}

}
