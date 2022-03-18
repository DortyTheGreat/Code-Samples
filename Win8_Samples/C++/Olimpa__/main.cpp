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

int main()
{
    long long a,b;
    cin >> a >> b;

    if( a == b && (a != 1)){
        cout << -1;
        return 0;
    }

    if (a == 1 && b == 1){
        cout << 1;
        return 0;
    }

    long long d = b - a;

    //a--;

    long long NB = 0;

    if ((a-1) % (d) == 0){
        NB = (a-1)/d;
    }else{
        NB = (a-1)/d + 1;
    }


    long long ans = NB * a;

    if (ans == 0){
        ans = 1;
    }
    cout << ans;
}
