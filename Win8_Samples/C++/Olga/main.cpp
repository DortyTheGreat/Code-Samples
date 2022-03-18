#include <iostream>

using namespace std;

int main()
{
    long long n,S1,S2;
    cin >> n >> S1 >> S2;
    bool flag1 = ( (S1) >= (n*64)) && ( (S2) >= (n*76)) ;
    if(flag1){
        cout << "YES";
    }else{
    cout << "NO";
    }
}
