#include <iostream>
#include <cmath>
using namespace std;


#define int long long

long long A_,B_;

bool IsSquare(long long number){
return (sqrt(number) == (long long)(sqrt(number)) );
}
long long pseudoInf = 10000000000000;
long long BestB = pseudoInf, BestA;

void Collect(long long a, long long b){
    if ( (b%2)&&(a%2) ){

    if (b < BestB){
        BestB = b;
        BestA = a;
    }
    }
}

void D1D2_Solve(long long D1, long long D2){
/// D2 > D1
if ((D1 + D2)%2 == 1 ){
    return; /// Ошибка, надо скипать
}
A_ = (D1+D2)/2 - 1;
B_ = D2 - A_;
    ////cout << D1 << " " << D2 << "  -  " << A_ << " " << B_ << endl;
    Collect(A_,B_);
}

void ItterateAllMultiMpliers(long long n4){

    if( IsSquare(n4) ){
            ///sqrt(n4), sqrt(n4)
            D1D2_Solve(sqrt(n4),sqrt(n4));
    }
    long long lim = sqrt(n4);
    for(int i=1;i<lim;i++){
        if(n4%i==0){
            ///i, n4/i;

            D1D2_Solve(i,n4/i);

        }
    }





}


signed main()
{
    int cou = 0;

    for(int i =11;i<100;i++){
        if((i%2 == 0 ) || (i % 7 == 0)){
            cou++;
            cout << i << " " << cou << endl;
        }
    }
    cout << cou;
}
