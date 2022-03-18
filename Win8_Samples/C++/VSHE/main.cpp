#include <iostream>
#include <cmath>
using namespace std;
long long n;
long long GetPseudoPerimeter(long long a, long long b){
if( a== 0 || b==0){return 0;}
if(a == 1){return b;}
if (b== 1){return a;}
return 2*(a+b-2);
}
long long GetTheRest(long long a, long long b){
return a*b - GetPseudoPerimeter(a,b);
}
long long regtriag(long long a){
if(a < n/2){
    return a;
}else{
return n-a;
}
}
long long trianpl(long long a,long long b){
if(b > a){
    swap(a,b);
}
//cout <<" " <<regtriag(b) << " "; //- max((n-max(a,b) ),n-min(a,b) )
return a - regtriag(b);

}
int main()
{

    cin >> n;
    long long a[10000];
    for(long long i=0;i<n;i++){
        cin >> a[i];
    }
    long long maxPoos=-10000;
    long long index1=-1;
    long long index2=-1;
    long long indr1=-1;
    long long indr2=-1;
    for(long long i=0;i<n;i++){
        for(long long j=i;j<n;j++){
            long long my = max(a[i],a[j]) - min(a[i],a[j]) -trianpl(i+1,j+1);
                    //cout << my  << " " <<max(a[i],a[j]) - min(a[i],a[j]) <<" " <<trianpl(i+1,j+1) << endl;
                if(maxPoos < my && i!= j){

                    maxPoos=my;
                    index1=max(a[i],a[j]);index2=min(a[i],a[j]);
                    indr1=i;
                    indr2=j;
                }
           // cout << i << " " << j << endl;
        }
    }
   // cout << endl;
   // cout << floor(pow(n,2)/2) << endl;
    //cout << (index1 - index2) << endl;
    //cout << abs(indr1-indr2 ) << endl;
    cout << (long long)(floor(n*n/2)) + maxPoos;

}
