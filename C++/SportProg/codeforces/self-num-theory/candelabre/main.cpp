#include <iostream>

#include <chrono>
#include <random>
int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);
/// [a;b]
int rnd(int a, int b) {
    return a + mt() % (b - a + 1);
}
int m = 13;
struct WTF{
    long long natural;
    long long imaginary;

    WTF(int64_t n,int64_t i ) : natural(n), imaginary(i){}

    WTF operator+ (const WTF& other) const{
        return WTF( (natural+other.natural)%m, (imaginary+other.imaginary)%m );
    }

    WTF operator* (const WTF& other) const{
        int64_t v = (natural*other.natural - imaginary*other.imaginary)%m;
        if (v < 0) v+= m;
        return WTF( v, (imaginary*other.natural + natural*other.imaginary)%m );
    }

};

using namespace std;
#include <fstream>

ofstream fout("out.txt");


int main()
{
    long long r;
    cin >> r;



    long long ans = 0;
    for(long long i = 0; i < r; ++i){
        ans += floor(sqrt(r*r - i * i));
    }

    cout << 1 + 4*ans;
    return 0;
}
