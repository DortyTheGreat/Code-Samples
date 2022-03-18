#include <iostream>

using namespace std;

long long NOD(long long a,long long b){

   if(a<b){swap(a,b);}
   while(1){
        a=a%b;
        if(a==0){break;}else{if(a<b){swap(a,b);}}
   }
  return b;

}

bool isCoprime(int a, int b) {

    if ( NOD(a, b) == 1)
        return 1;
    else
        return 0;
}

int f(int n){
    int ans = 0;
    for(int i =1;i<=n;i++){
        if (isCoprime(i,n)){
            ans++;
        }
    }
    return ans;
}

int main()
{
    int ans = 0;
    for(int i = 0;i<1001;i++){
        if (f(9*i) == 9 * f(i)){
            ans++;
            cout << i << " " << f(i) << " " << f(9*i) << endl;
        }
    }

    cout << ans;
    return 0;
}
