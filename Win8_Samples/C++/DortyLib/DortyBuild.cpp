#include <iostream>
#include "iostream"
#include <cmath>

using namespace std;

int NOD(int a,int b){

   if(a<b){swap(a,b);}
   while(1){

    a=a%b;
    if(a==0){break;}else{if(a<b){swap(a,b);}}

   }
  return b;

}

#include "iostream"

using namespace std;





int main()
{
     
    int a,b;
    cin >> a >> b;
    cout << NOD(a,b);
    /// Комметнтарий на русском
}

