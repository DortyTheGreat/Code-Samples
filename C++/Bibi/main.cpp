#include <iostream>

using namespace std;

int F(int n){
    if (n == 0){
        return 0;
    }
    if (n%2 == 0){
        return F(n/2);
    }
    return 1 + F(n-1);
}

int main()
{
    for(int i =0;i<10000;i++){
        if (F(i) == 12){
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}
