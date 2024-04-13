#include <iostream>

using namespace std;

int digitprod(int n)
{
    int mul = 1;
    while (n != 0) {
        mul *= n % 10;
        n = n / 10;
    }
    return mul;
}

int S(int x){

    for(int i = 1; i < 1000 * 600; ++i){
        if (digitprod(i) == x) return i;
    }
    return 0;

}

int main()
{
    int maxi = -1; int arg = -1;
    for(int i = 1; i <= 10000; ++i){
        //cout << S(i) << endl;
        int v = S(i);
        if (maxi < v){
            maxi = v;
            arg = i;
            cout << arg << " " << maxi << endl;
        }
    }
    cout << arg << " " << maxi << endl;
    return 0;
}
