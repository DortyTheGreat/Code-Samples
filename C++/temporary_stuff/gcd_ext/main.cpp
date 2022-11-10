


#include <iostream>
#include <utility>
using namespace std;
/// source : https://www.cyberforum.ru/cpp-beginners/thread2679363.html

/*

template <typename T>
T gcd_ext(T a,T b,T& x,T& y) {
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    T d=gcd_ext(b,a%b,y,x);
    y-=(a/b)*x;
    return d;
}
*/

template <typename T>
T gcd_ext(T a,T b,T& x,T& y) {

    while(b){

    }
    x = 1;
    y = 0;
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    T d=gcd_ext(b,a%b,y,x);
    y-=(a/b)*x;
    return d;
}

/// https://stackoverflow.com/questions/22991075/extended-euclid-algorithm-is-there-non-recursive-version-of-it
template <typename T>
T extended_gcd(T a,T b, T& x, T& y){
    T unPrev = 1;
    T vnPrev = 0;
    x = 0;
    y = 1;
    T bn;

    while (b){
        bn = a / b;
        unPrev -= bn * x;
        vnPrev -= bn * y;
        /// Теперь prev - это новый cur
        if (! (a%=b) ) return b;



        bn = b / a;
        b %= a;
        x -= bn * unPrev;
        y -= bn * vnPrev;


    }
    x = unPrev;
    y = vnPrev;
    return a;
}
/// https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
template <typename T>
T wiki_extended_gcd(T a,T b, T& x, T& y){
    T s = 0, old_s = 1;
    T r = b, old_r = a;

    while (r){
        T quotient = old_r / r;
        old_r -= quotient *r;
        old_s -= quotient * s;
        swap(old_r,r);
        swap(old_s,s);
    }

    x = old_s;
    if (b == 0){y = 0; return old_r;}
    y = (old_r - old_s * a) / b;
    return old_r;

}
/// a*x + b*y = c
/// даёт (-1,-1), если решения нет, в ином случае решение с минимальным неотрицательным x.
pair<int,int> diophantus(int a, int b, int c){
    int x0,y0;

    int d=wiki_extended_gcd(a,b,x0,y0);
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
    const int sz = 200;
    for(int n = 1;n < sz;++n){
        for(int x = 1;x < sz; ++x){
            for (int y = 1; y < sz; ++y){
                if (f_(n,x,y) != f3(n,x,y)){
                    cout << n << " " << x << " "  << y << endl;
                    cout << "gosunov: " << f_(n,x,y) << endl;
                    cout << "dorty4: " << f3(n,x,y) << endl << endl;
                }
            }
        }
    }




}

