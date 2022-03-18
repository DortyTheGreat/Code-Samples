#include <iostream>
#include <set>
using namespace std;

int NOD(int a,int b){

   if(a<b){swap(a,b);}
   while(1){

    a=a%b;
    if(a==0){break;}else{if(a<b){swap(a,b);}}

   }
  return b;

}

int main()
{

    multiset<int> org,cur;
    int k;
    int m;

    int num;

    cin >> k >> m;

    int STARTI,KIKI=0;

    cin >> num;
    STARTI = num;



    for(int i=0;i<m-1;i++){
        int old = num;
        cin >> num;
        old = old/NOD(old,num);
        //cout << old << " ";

        if(cur.find(old) != cur.end() ){
            cur.erase(cur.find(old));
            cur.insert(old-1);
        }else{
        org.insert(old);
        STARTI /= old;
        KIKI++;
        cur.insert(old-1);
        }
    }

    cout << endl;

    for (auto i : org){
        cout << i << " ";
    }
    cout << endl;
    for(int i = 0;i<k-KIKI;i++){
        if(i == 0){cout << STARTI << " ";}else{
            cout << "1 ";
        }
    }

    cout << endl;

    for (auto i : cur){
        //cout << i << " ";
    }

}
