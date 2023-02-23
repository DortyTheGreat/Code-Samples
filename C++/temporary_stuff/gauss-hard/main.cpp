#include <iostream>
#include <cmath>
using namespace std;


typedef   uint64_t    u64;


#define FORCE_INLINE __attribute__((always_inline)) inline

FORCE_INLINE u64 isqrt(const u64& n)
{
    if (n == 0)
        return 0;

    u64 a = n;
    u64 b = 1;
    u64 c;

    if (c = (a >> 32))
    {
        a = c;
        b <<= 16;
    }
    if (c = (a >> 16))
    {
        a = c;
        b <<= 8;
    }
    if (c = (a >> 8))
    {
        a = c;
        b <<= 4;
    }
    if (c = (a >> 4))
    {
        a = c;
        b <<= 2;
    }
    if (c = (a >> 2))
    {
        a = c;
        b <<= 1;
    }

    if (a <= 1)
        b += b >> 1;
    else
        b <<= 1;

    do
    {
        a = b;
        b = (b + n / b) >> 1;
    } while (b < a);

    return a;
}

FORCE_INLINE u64 fast_sqrt_c(const uint64_t& n)
{
  uint64_t g = 0x80000000; // initial guess
  uint64_t b = 0x80000000; // 'additional' bit is in position 7
  uint64_t g2;
  for (;;)
  {
    g2 = g*g;
    if ( g2 == n )
      break;        // an exact match is found
    if ( g2 > n )
      g ^= b;       // here g*g > n, remove the added bit
    b >>= 1;        // shift right the 'addional' bit
    if ( b == 0 )
      break;        // the 'additional' bit was shifted out, the iteration is complete
    g |= b;         // add the current 'additional bit'
  }
  return g;
}

int main()
{
    u64 r;
    cin >> r;

    u64 ans = 0;

    u64 sr = r * r;
    u64 incr = r;
    for(u64 i = 0; i < r; ++i){
        while(incr*incr > sr - i * i)
            --incr;
        ans += incr;
    }



    cout << 1 + 4*ans;
    return 0;
}
