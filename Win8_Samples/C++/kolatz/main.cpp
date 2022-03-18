#include <iostream>

using namespace std;
long long const NUM_CO=1;

long long func(long long arg, long long cou, int temp){
if(arg == NUM_CO){ cout << temp << " "; return cou;}
if(arg%2){

    return func(arg*3+1,cou+1,0);

}else{
return func(arg/2,cou+1,temp+1);
}

}
int main()
{
    long long START=1;
    for(long long i=START;i<START+200;i++){
       cout << endl << i << ":  ";
       func(i,0,0);
    }
}
