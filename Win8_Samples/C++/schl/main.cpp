#include <cmath>
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
long NOK(long a, long b){
return (a/NOD(a,b))*(b/NOD(a,b))*NOD(a,b);
}

int main()
{
    long long Data[500][500];
   long long n,m,dX=1,flag=1,flag2=0, dY=1;
   cin >> n >> m;
   if (m == 1){swap(n,m);}
   for(long long i=0;i<n;i++){
    for(long long j=0;j<m;j++){
            cin >> Data[i][j];



            if( (i == 0) && (j == 1)){dX =Data[0][1] - Data[0][0];flag2=1; if(dX <= 0){flag = 0;}  }
            if(flag2 && (j > 0)){ if( Data[i][j] - Data[i][j-1] != (dX+i) ){flag=0;}

            int NOD_ = NOD(Data[i][j-1],Data[i][j]);
            int N1 = Data[i][j-1] / NOD_;
            int N2 = Data[i][j] / NOD_;
            if(N2 - N1 != 1){flag = 0;}

             }

    }
   }
   if((n > 1) && (m > 1)){
    dX = Data[0][0] / NOD(Data[0][0],Data[0][1]);
    dY = Data[0][0] / NOD(Data[0][0],Data[1][0]);

   	 if(dY <= 0){flag = 0;}
   	 if(dX <= 0){flag = 0;}

    for(long long i=0;i<n;i++){
    for(long long j=0;j<m;j++){
            long long Pr = (dX+j)*(dY+i);
            if (Data[i][j] != Pr){flag=0;}

    }
   }
   }

   //cout << dX;

    if(flag){cout << "true";}else{cout << "false";}
}
