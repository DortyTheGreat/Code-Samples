#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int a[1000],o[1000],n,i,j,k,l=3,p=0,u=0;
    cin >> n;
    for (i=0; i<n; i++){
        cin >> a[i];
        o[i]=a[i];
    }
    for (k=0; k<n; k++)
    for (i=0; i<n-1; i++)
        if ((a[i])>(a[i+1])){
            j=a[i];
            a[i]=a[i+1];
            a[i+1]=j;
        }
    while (l<n){
        if (o[p]!=a[0] && o[p]!=a[1] && o[p]!=a[2] && u<=3){
            a[l]=o[p];
            p++;
            l++;
        }
        else{ if (u>=3){ a[l]=o[p];l++;}
            p++;
            u++;}
    }
    for (i=0; i<n; i++)
        cout << a[i] << " ";

    return 0;
}
