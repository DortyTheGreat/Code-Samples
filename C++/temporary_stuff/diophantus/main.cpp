#include <iostream>

using namespace std;
template<typename T>
T mod_inverse(T num, T mod){
    return 1<num ? mod - mod_inverse(mod%num,num)*mod/num : 1;
}


template<typename T>
T Dorty_EXT(T num, T mod){
    T inverse = 0;
    while (num != 0)
    return 1<num ? mod - mod_inverse(mod%num,num)*mod/num : 1;
}

template<typename T>
T gcd(T a, T b){
    while(a %=b) if (!(b %= a)) return a;
    return b;
}


/// a*x + b*y = c
/// даёт (-1,-1), если решения нет, в ином случае решение с минимальным неотрицательным x.
pair<int,int> diophantus(int a, int b, long long c){
    int g = gcd(a,b);
    if (c % g != 0) return {-1,-1};
    a /= g; b /= g; c/= g;
    pair<int,int> ret;

    ret.first = (c * mod_inverse(a,b)) % b;
    ret.second = (c - a*ret.first)/b;
    return {ret.first,ret.second};
}



#include <vector>
int main()
{
    int A,B,C;
    cin >> A >> B >> C;
    auto p = diophantus(A,B,C);
    cout << p.first << " " << p.second;
    return 0;
}
