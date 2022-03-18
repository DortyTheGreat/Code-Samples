#include <cmath>

using namespace std;

long long NOD(long long a,long long b){

   if(a<b){swap(a,b);}
   while(1){
        a=a%b;
        if(a==0){break;}else{if(a<b){swap(a,b);}}
   }
  return b;

}

bool IsPrime(long long a){
    if(a < 2){return 0;}
    if(sqrt(a) == int(sqrt(a))){return 0;}
    for(int i=2;i<sqrt(a);i++){
        if(a%i == 0){return 0;}
    }
    return 1;
}
