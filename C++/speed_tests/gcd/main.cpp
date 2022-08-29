#include <iostream>
#include <chrono>
class Clock2{
private:
    long long last_time;



public:

    Clock2(){
        last_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    void tick() {
        long long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::cout  <<(time-last_time) << std::endl;
        last_time = time;
    }

    void tick(float div, bool _endl = 1) {
        long long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::cout  <<float(time-last_time) / div << " ns";
        if (_endl){std::cout << std::endl;}
        last_time = time;
    }

    void tick(std::string text, float div){
        tick(div,0);
        std::cout <<" - "<< text << std::endl;
    }


};

Clock2 MainClock;

#include <numeric>

unsigned short rand16(){return rand();}
unsigned int rand32(){return (unsigned int)(rand16()) * 65535 + rand16();}
unsigned long long rand64(){return (unsigned long long)(rand32()) * 0xffffffff + rand32();}
__uint128_t rand128(){return (__uint128_t)(rand64()) * 0xffffffffffffffff + rand64();}


/// Чуть быстрее __gcd, для int
template<typename T>
T gcd(T a, T b)
{
    T c;
    while (b)
    {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}

/// Чуть быстрее __gcd, для int
template<typename T>
inline T inline_gcd(T a, T b)
{
    while(a %=b) if (!(b %= a)) return a;
    return b;
}

unsigned long long gcd_chin(unsigned long long a, unsigned long long b) {
    if (b == 0)
        return a;

    int shift = __builtin_ctzll(a | b);
    b >>= __builtin_ctzll(b);

    while (a) {
        a >>= __builtin_ctzll(a);

        if (a < b)
            std::swap(a, b);

        a -= b;
    }

    return b << shift;
}

template<typename T>
T cool_gcd(T a, T b) {
	while(b ^= a ^= b ^= a = a % b);
	return a;
}


template<typename T>
inline T binary_gcd(T a, T b) {
  if (a == 0 || b == 0) return a + b;
  unsigned char n = __builtin_ctzll(a);
  unsigned char m = __builtin_ctzll(b);
  a >>= n;
  b >>= m;
  n = std::min(n, m);
  while (a != b) {
    T d = a - b;
    unsigned char s = __builtin_ctzll(d);
    bool f = a > b;
    b = f ? b : a;
    a = (f ? d : -d) >> s;
  }
  return a << n;
}


template<typename T>
inline T binary_gcd2(T a, T b) {
  if (a == 0 || b == 0) return a + b;
  unsigned char n = __builtin_ctzll(a);
  unsigned char m = __builtin_ctzll(b);
  a >>= n;
  b >>= m;
  n = std::min(n, m);
  while (a != b) {
    T d = a - b;
    unsigned char s = __builtin_ctzll(d);
    if (a > b){
        a = d >> s;
    }else{
        b = a;
        a = -d >> s;
    }
  }
  return a << n;
}

unsigned int u32_bin_gcd(unsigned int a, unsigned int b)
{
  unsigned char shift=__builtin_ctz(a|b);
  a>>=__builtin_ctz(a);

  do
   {
    b>>=__builtin_ctz(b);

    if (a>b) std::swap(a,b);
    b-=a;
   } while (b);

  return a << shift;
}

unsigned long long u64_bin_gcd(unsigned long long a, unsigned long long b)
{
  unsigned char shift=__builtin_ctzll(a|b);
  a>>=__builtin_ctzll(a);

  do
   {
    b>>=__builtin_ctzll(b);

    if (a>b) std::swap(a,b);
    b-=a;
   } while (b);

  return a << shift;
}

using namespace std;
#include <algorithm>
int main()
{
    MainClock.tick();
    const int itterations = 10000;
    const int rerand_i = 300;
    /*
    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),g,_g, b_, b2, chin, cool, inli;
        g = gcd(a,b);
        _g = __gcd(a,b);
        b_ = binary_gcd(a,b);
        b2 = binary_gcd2(a,b);
        chin = gcd_chin(a,b);
        cool = cool_gcd(a,b);
        inli = inline_gcd(a,b);
        if (!( g == _g && _g == b_ && b_ == b2 && b2 == chin && chin == cool && cool == inli )){
            cout << g << " " << _g << " " << b_ << " " << b2 << " " << chin << " " << cool << " " << inli << endl;
        }
    }
    */

    for(int i = 0;i<itterations;++i){
        unsigned short a = rand16(),b = rand16(),c;
        for(int j = 0;j<rerand_i;++j){
            c = gcd(a,b);
        }
    }
    MainClock.tick("int16 gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned short a = rand16(),b = rand16(),c;
        for(int j = 0;j<rerand_i;++j){
            c = __gcd(a,b);
        }
    }
    MainClock.tick("int16 __gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned short a = rand16(),b = rand16(),c;
        for(int j = 0;j<rerand_i;++j){
            c = binary_gcd(a,b);
        }
    }
    MainClock.tick("int16 gcd_bin", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned short a = rand16(),b = rand16(),c;
        for(int j = 0;j<rerand_i;++j){
            c = binary_gcd2(a,b);
        }
    }
    MainClock.tick("int16 gcd_bin2", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned short a = rand16(),b = rand16(),c;
        for(int j = 0;j<rerand_i;++j){
            c = gcd_chin(a,b);
        }
    }
    MainClock.tick("int16 gcd_chin", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned short a = rand16(),b = rand16(),c;
        for(int j = 0;j<rerand_i;++j){
            c = cool_gcd(a,b);
        }
    }
    MainClock.tick("int16 cool_gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned short a = rand16(),b = rand16(),c;
        for(int j = 0;j<rerand_i;++j){
            c = inline_gcd(a,b);
        }
    }
    MainClock.tick("int16 inline_gcd", rerand_i * itterations);



    cout << endl;




    for(int i = 0;i<itterations;++i){
        unsigned int a = rand32(),b = rand32(),c;
        for(int j = 0;j<rerand_i;++j){
            c = gcd(a,b);
        }
    }
    MainClock.tick("int32 gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned int a = rand32(),b = rand32(),c;
        for(int j = 0;j<rerand_i;++j){
            c = __gcd(a,b);
        }
    }
    MainClock.tick("int32 __gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned int a = rand32(),b = rand32(),c;
        for(int j = 0;j<rerand_i;++j){
            c = binary_gcd(a,b);
        }
    }
    MainClock.tick("int32 gcd_bin", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned int a = rand32(),b = rand32(),c;
        for(int j = 0;j<rerand_i;++j){
            c = binary_gcd2(a,b);
        }
    }
    MainClock.tick("int32 gcd_bin2", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned int a = rand32(),b = rand32(),c;
        for(int j = 0;j<rerand_i;++j){
            c = gcd_chin(a,b);
        }
    }
    MainClock.tick("int32 gcd_chin", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned int a = rand32(),b = rand32(),c;
        for(int j = 0;j<rerand_i;++j){
            c = cool_gcd(a,b);
        }
    }
    MainClock.tick("int32 cool_gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned int a = rand32(),b = rand32(),c;
        for(int j = 0;j<rerand_i;++j){
            c = inline_gcd(a,b);
        }
    }
    MainClock.tick("int32 inline_gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned int a = rand32(),b = rand32(),c;
        for(int j = 0;j<rerand_i;++j){
            c = u32_bin_gcd(a,b);
        }
    }
    MainClock.tick("int32 bin_special", rerand_i * itterations);
    cout << endl;





    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            c = gcd(a,b);
        }
    }
    MainClock.tick("int64 gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            c = __gcd(a,b);
        }
    }
    MainClock.tick("int64 __gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            c = binary_gcd(a,b);
        }
    }
    MainClock.tick("int64 gcd_bin", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            c = binary_gcd2(a,b);
        }
    }
    MainClock.tick("int64 gcd_bin2", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            c = gcd_chin(a,b);
        }
    }
    MainClock.tick("int64 gcd_chin", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            c = cool_gcd(a,b);
        }
    }
    MainClock.tick("int64 cool_gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            c = inline_gcd(a,b);
        }
    }
    MainClock.tick("int64 inline_gcd", rerand_i * itterations);

    for(int i = 0;i<itterations;++i){
        unsigned long long a = rand64(),b = rand64(),c;
        for(int j = 0;j<rerand_i;++j){
            c = u64_bin_gcd(a,b);
        }
    }
    MainClock.tick("int64 special_bin", rerand_i * itterations);


    cout << "Hello world!" << endl;
    return 0;
}
