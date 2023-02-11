#include <iostream>

using namespace std;
template<typename T>
T mod_inverse(T num, T mod){
    cout << num << " " << mod << " " << (1<num) << endl;
    return num != 0 ? mod - mod_inverse(mod%num,num)*mod/num : mod;
}

template<typename T>
T gcd(T a, T b){
    while(a %=b) if (!(b %= a)) return a;
    return b;
}

int extended_euclidean(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = extended_euclidean(b, a % b, y, x);
    y -= x * (a / b);
    return d;
}

int inv(int a, int m) {
    int x, y;
    int g = extended_euclidean(a, m, x, y);
    if (g != 1) {
        cout << "No solution!";
    }
    else {
        x = (x % m + m) % m;
        return x;
    }
}





/// a*x + b*y = c
/// даёт (-1,-1), если решения нет, в ином случае решение с минимальным неотрицательным x.
pair<int,int> diophantus(int a, int b, long long c){
    int g = gcd(a,b);
    if (c % g != 0) return {-1,-1};
    a /= g; b /= g; c/= g;
    pair<int,int> ret;
    cout << "inv: " << mod_inverse(a,b) << endl << endl;
    ret.first = (c * inv(a%b,b)) % b;
    ret.second = (c - a*ret.first)/b;
    return {ret.first,ret.second};
}





#include <vector>
int main()
{
    cout << inv(1234, 567) << endl;
    cout << inv(100, 567) << endl;

    cout << inv(1,4) << endl;

    cout << inv(7,4) << endl;

    cout << inv(3,4) << endl;

    int A,B,C;
    cin >> A >> B >> C;
    auto p = diophantus(A,B,C);
    cout << p.first << " " << p.second;
    return 0;
}
