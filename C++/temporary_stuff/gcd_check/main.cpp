#include <iostream>
#include <ctime>
using namespace std;

using u64 = unsigned long long;
using i8 = char;

template<typename T>
inline T binary_gcd(T a, T b) {
  if (a == 0 || b == 0) return a + b;
  i8 n = __builtin_ctzll(a);
  i8 m = __builtin_ctzll(b);
  a >>= n;
  b >>= m;
  n = min(n, m);
  while (a != b) {
    T d = a - b;
    i8 s = __builtin_ctzll(d);
    bool f = a > b;
    b = f ? b : a;
    a = (f ? d : -d) >> s;
  }
  return a << n;
}
  // namespace BinaryGCDImpl

  /// Чуть быстрее __gcd
template<typename T>
inline T gcd(T a, T b)
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



int main()
{
    srand(time(0));

    for(int i = 0;i<10000;++i){
        __uint128_t a = rand() % 100000;
        __uint128_t b = rand() % 100000;
        for(int j = 0; j < 1000; ++j){

            binary_gcd(a,b);
        }

    }

    cout << "Hello world!" << endl;
    return 0;
}
