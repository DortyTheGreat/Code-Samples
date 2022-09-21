

#include <iostream>
#include <utility>
using namespace std;
/// source : https://www.cyberforum.ru/cpp-beginners/thread2679363.html

long long gcd_ext(long long a,long long b,long long& x,long long& y) {
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    long long d=gcd_ext(b,a%b,x,y);
    x-=(a/b)*y;
    swap(x,y);
    return d;
}

/// a*x + b*y = c
/// даёт (-1,-1), если решения нет, в ином случае решение с минимальным неотрицательным x.
pair<int,int> diophantus(int a, int b, int c){
    long long x0,y0;

    int d=gcd_ext(a,b,x0,y0);
    if(c%d){
        return {-1,-1};
    }
    int p=x0*c/d;
    int q=b/d;
    int x=(p%q+q)%q;
    int y=(c-a*x)/b;
    return {x,y};
}
bool f3(int n, int a, int b){
    return (diophantus(a,b,n).second >=0);
}

bool f_(int n, int a, int b) {
    for (int k = 0; k * a <= n; ++k) {
        if ((n - k * a) % b == 0)
            return true;
    }
    return false;
}

int main()
{
    cout << f3(15,5,7) << endl;

    for(int n = 1;n < 1000;++n){
        for(int x = 1;x < 1000; ++x){
            for (int y = 1; y < 1000; ++y){
                if (f_(n,x,y) != f3(n,x,y)){
                    cout << n << " " << x << " "  << y << endl;
                    cout << "gosunov: " << f_(n,x,y) << endl;
                    cout << "dorty4: " << f3(n,x,y) << endl << endl;
                }
            }
        }
    }




}
