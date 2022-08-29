/// Чуть быстрее __gcd, для int
template<typename T>
inline T gcd(T a, T b)
{
    while(a %=b) if (!(b %= a)) return a;
    return b;
}
/// Для long long и выше - предпочтительнее -
/// https://github.com/NyaanNyaan/library/blob/master/math-fast/gcd.hpp
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

