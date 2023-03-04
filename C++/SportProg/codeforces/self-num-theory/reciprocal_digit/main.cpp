#include <iostream>

/// src: https://stackoverflow.com/questions/804934/getting-a-specific-digit-from-a-ratio-expansion-in-any-base-nth-digit-of-x-y

using namespace std;

typedef   uint64_t    u64;
typedef   uint64_t    i64;

/// даёт n-тое число в расширении числа x/y.
/// Например digits2(1,7,8) = 4, ведь 1/7 = 0.1428571{4}28... -> 4
u64 digits2(u64 x,u64 y, u64 n1)
{
  // the nth digit of x/y = floor(10 * (10^(n-1)*x mod y) / y) mod 10.
  u64 m = n1-1;
  u64 A = 1, B = 10;
  while (m > 0)
  {
    // loop invariant: 10^(n1-1) = A*(B^m) mod y

    if (m & 1)
    {
      // A = (A * B) % y    but javascript doesn't have enough sig. digits
      A = (A * B) % y;
    }
    // B = (B * B) % y    but javascript doesn't have enough sig. digits
    B = (B * B) % y;
    m >>= 1;
  }

  x = x %  y;
  // A = (A * x) % y;
  A = (A * x) % y;



  return (10*A/y)%10;

}


int main()
{
    u64 a,b,c;
    cin >> a >> b >> c;
    cout << digits2(a,b,c);


    return 0;
}
