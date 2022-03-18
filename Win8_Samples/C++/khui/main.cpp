#include <iostream>

#define int long long

using namespace std;


long long NOD(long long a,long long b){

   if(a<b){swap(a,b);}
   while(1){
        a=a%b;
        if(a==0){break;}else{if(a<b){swap(a,b);}}
   }
  return b;

}

signed main()
{
    int k;
    cin >> k;
    for(int i =0;i<k;i++){


        int a,b;
        int nA,nB;
        cin >> a >> b;
        nA = a/NOD(a,b);
        nB = b/NOD(a,b);

        //if (nB == nA){
          //  cout << "-1 1" << endl;
           // continue;
        //}

        if (nB < nA){
            swap(nB,nA);
            int a1 = -1 * nA * nA;

            int b1 = nB * nB;

            cout << b1 << " " << a1 << endl;
        }else{
            int a1 = -1 * nA * nA;

            int b1 = nB * nB;

            cout << a1 << " " << b1 << endl;
        }




    }
    return 0;
}
