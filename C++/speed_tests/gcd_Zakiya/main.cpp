// Daniel Lemire in this article
// https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/
// presented benchmark comparisons of different implementations of Stein's (binary) gcd algorithm.
// The wikipedia (iterative) implementation of the algorithm was noted to be very inefficient.
// Lemire presented benchmarked comparisons of various implementations, original code below.
// https://github.com/lemire/Code-used-on-Daniel-Lemire-s-blog/blob/master/2013/12/26/gcd.cpp
// I have modified the output to make it explicit and clear, modified the code in some functions
// to make them easier to follow and standardized variable names, and added the Ruby implementation.
// I also ordered the ouput to show fastest to slowest.
// The results: gcdwikipedia7fast32 is fastest by far; the implementation shown in widipedia is slowest.
// To compile: g++ -O3 gcdbenchmarks.cpp -o gcdbenchmarks; and runs as  ./gcdbenchmarks

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <utility>

//#define ctz_shift_bits 8;
//#define ctz_mask  255;  //2**ctz_shift - 1;


using namespace std;
class WallClockTimer
{
public:
    struct timeval t1, t2;
public:
    WallClockTimer() : t1(), t2() {
        gettimeofday(&t1,0);
        t2 = t1;
    }
    void reset() {
        gettimeofday(&t1,0);
        t2 = t1;
    }
    int elapsed() {
        return (t2.tv_sec * 1000 + t2.tv_usec / 1000) - (t1.tv_sec * 1000 + t1.tv_usec / 1000);
    }
    int split() {
        gettimeofday(&t2,0);
        return elapsed();
    }
};

// Create ctz (count trailing zeros) function to mimic __builtin_ctz compiler directive
// Create to do 6-bit rights shifts at once. Can increase to hearts content.
//int ctz_shift_bits = 8;
//int ctz_mask  = 255;  // 2**ctz_shift_bits - 1;
int ctz_bits[256] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                     4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};

// from http://en.wikipedia.org/wiki/Binary_GCD_algorithm
unsigned int gcdwikipedia2(unsigned int u, unsigned int v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
        u >>= 1;
        v >>= 1;
    }

    while ((u & 1) == 0) u >>= 1;

    do {
        while ((v & 1) == 0) v >>= 1;
        if (u > v) {
            unsigned int t = v;
            v = u;
            u = t;
        }
        v = v - u;
    } while (v != 0);
    return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire and R. Corderoy
unsigned int gcdwikipedia2fast(unsigned int u, unsigned int v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) {
            unsigned int t = v;
            v = u;
            u = t;
        }
        v = v - u;
    } while (v != 0);
    return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire and R. Corderoy
unsigned int gcdwikipedia2fastswap(unsigned int u, unsigned int v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if(u>v) std::swap(u,v);
        v = v - u;
    } while (v != 0);
    return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire and R. Corderoy
unsigned int gcdwikipedia2fastxchg(unsigned int u, unsigned int v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
       if (u > v) asm volatile("xchg %0, %1\n":  "+r"(u), "+r" (v):);
        v = v - u;
    } while (v != 0);
    return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire, R. Corderoy, K. Willets
unsigned int gcdwikipedia3fast(unsigned int u, unsigned int v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u == v)
          break;
        else if (u > v) {
          unsigned int t = v;
          v = u;
          u = t;
        }
        v = v - u;
    } while (true);
    return u << shift;
}
// based on wikipedia's article,
// fixed by D. Lemire and R. Corderoy (twice)
unsigned int gcdwikipedia4fast(unsigned int u, unsigned int v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        unsigned m;
        v >>= __builtin_ctz(v);
        m = (v ^ u) & -(v < u);
        u ^= m;
        v ^= m;
        v -= u;
    } while (v != 0);
    return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire and R. Corderoy (twice)
unsigned int gcdwikipedia4fast_a(unsigned int u, unsigned int v)
{
    int shift;
    unsigned int t;
    if (u == 0) return v;
    if (v == 0) return u;

    t = (u | v); shift = 0;
    while ((t & 255) == 0) {t >>= 8; shift += 8;}
    shift += ctz_bits[t & 255];

    //while ((u & ctz_mask) == 0) u >>= ctz_shift_bits;
    //u >>= ctz_bits[u & ctz_mask];
    while ((u & 255) == 0) u >>= 8;
    u >>= ctz_bits[u & 255];

    do {
        unsigned m;
        //while ((v & ctz_mask) == 0) v >>= ctz_shift_bits;
        //v >>= ctz_bits[v & ctz_mask];
        while ((v & 255) == 0) v >>= 8;
        v >>= ctz_bits[v & 255];

        m = (v ^ u) & -(v < u);
        u ^= m;
        v ^= m;
        v -= u;
    } while (v != 0);
    return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire,  K. Willets
unsigned int gcdwikipedia5fast(unsigned int u, unsigned int v)
{
     int shift, uz, vz;
     uz = __builtin_ctz(u);
     if ( u == 0) return v;
     vz = __builtin_ctz(v);
     if ( v == 0) return u;
     shift = uz > vz ? vz : uz;
     u >>= uz;
     do {
       v >>= vz;
       if (u > v) {
         unsigned int t = v;
         v = u;
         u = t;
       }
       v = v - u;
       vz = __builtin_ctz(v);
     } while( v != 0 );
     return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire,  K. Willets
unsigned int gcdwikipedia6fastxchg(unsigned int u, unsigned int v)
{
     int shift, uz, vz;
     uz = __builtin_ctz(u);
     if ( u == 0) return v;
     vz = __builtin_ctz(v);
     if ( v == 0) return u;
     shift = uz > vz ? vz : uz;
     u >>= uz;
     do {
       v >>= vz;
       if (u > v) asm volatile("xchg %0, %1\n":  "+r"(u), "+r" (v):);
       v = v - u;
       vz = __builtin_ctz(v);
     } while( v != 0 );
     return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire,  K. Willets
unsigned int gcdwikipedia7fast(unsigned int u, unsigned int v)
{
     int shift, uz, vz;
     if ( u == 0) return v;
     if ( v == 0) return u;
     uz = __builtin_ctz(u);
     vz = __builtin_ctz(v);
     shift = uz > vz ? vz : uz;
     u >>= uz;

     do {
       v >>= vz;
       long long int diff = v ;
       diff -= u;
       vz = __builtin_ctz(diff);
       if ( diff == 0 ) break;
       if ( diff <  0 ) u = v;
       v = abs(diff);

     } while( 1 );
     return u << shift;
}

// based on wikipedia's article,
// fixed by D. Lemire,  K. Willets
unsigned int gcdwikipedia7fast32(unsigned int u, unsigned int v)
{
     int shift, uz, vz;
     if ( u == 0) return v;
     if ( v == 0) return u;
     uz = __builtin_ctz(u);
     vz = __builtin_ctz(v);
     shift = uz > vz ? vz : uz;
     u >>= uz;
     do {
       v >>= vz;
       int diff = v;
       diff -= u;
       if ( diff == 0 ) break;
       vz = __builtin_ctz(diff);
       if ( v <  u ) u = v;
       v = abs(diff);

     } while( 1 );
     return u << shift;
}
unsigned int gcdwikipedia7fast32_a(unsigned int u, unsigned int v)
{
     int shift, uz, vz, tmp;
     if ( u == 0) return v;
     if ( v == 0) return u;

     uz = 0;
     while ((u & 255) == 0) {u >>= 8; uz += 8;}
     uz += ctz_bits[u & 255]; u >>= ctz_bits[u & 255];

     vz = 0;
     while ((v & 255) == 0) {v >>= 8; vz += 8;}
     vz += ctz_bits[v & 255]; v >>= ctz_bits[v & 255];

     shift = uz > vz ? vz : uz;
     do {
       int diff = v;
       diff -= u;
       if ( diff == 0 ) break;

       tmp = diff; vz = 0;
       while ((tmp & 255) == 0) {tmp >>= 8; vz += 8;}
       vz += ctz_bits[tmp & 255];

       if ( v <  u ) u = v;
       v = abs(diff);
       v >>= vz;

     } while( 1 );
     return u << shift;
}

// best from http://hbfs.wordpress.com/2013/12/10/the-speed-of-gcd/
unsigned gcd_recursive(unsigned a, unsigned b)
{
    if (b)
        return gcd_recursive(b, a % b);
    else
        return a;
}

// from http://hbfs.wordpress.com/2013/12/10/the-speed-of-gcd/
unsigned gcd_iterative_mod(unsigned a, unsigned b)
{
    while (b)
    {
        unsigned t=b;
        b=a % b;
        a=t;
    }
    return a;
}

unsigned basicgcd(unsigned u, unsigned v) {
    return (u % v) == 0 ? v :  basicgcd(v, u % v);
}

// attributed to  Jens
// Franke by Samuel Neves
unsigned gcdFranke (unsigned u, unsigned v)
{
  unsigned shift, s0, s1;
  if(0 == u) return v;
  if(0 == v) return u;
  s0 = __builtin_ctz(u);
  s1 = __builtin_ctz(v);
  shift = s0 < s1 ? s0 : s1;
  u >>= s0;
  v >>= s1;
  while (u != v)
  {
    if (u < v)
    { v -= u; v >>= __builtin_ctz(v); }
    else
    { u -= v; u >>= __builtin_ctz(u); }
  }
  return u << shift;
}

unsigned rubygcd(long x, long y)
{
    unsigned long u, v, t;
    int shift;
    if (x == 0) return y;
    if (y == 0) return x;

    if (x < 0) x = -x;
    if (y < 0) y = -y;

    u = (unsigned long)x;
    v = (unsigned long)y;
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
    u >>= 1;
    v >>= 1;
    }

    while ((u & 1) == 0) u >>= 1;

    do {
    while ((v & 1) == 0) v >>= 1;

    if (u > v) {
        t = v;
        v = u;
        u = t;
    }
    v = v - u;
    } while (v != 0);

    return (long)(u << shift);
}

unsigned rubygcd_a(long x, long y)
{
    unsigned long u, v, t;
    int shift;
    if (x == 0) return y;
    if (y == 0) return x;

    if (x < 0) x = -x;
    if (y < 0) y = -y;

    u = (unsigned long)x;
    v = (unsigned long)y;
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
    u >>= 1;
    v >>= 1;
    }

    //while ((u & ctz_mask) == 0) u >>= ctz_shift_bits;
    //u >>= ctz_bits[u & ctz_mask];
    while ((u & 255) == 0) u >>= 8;
    u >>= ctz_bits[u & 255];

    do {
    //while ((v & ctz_mask) == 0) v >>= ctz_shift_bits;
    //v >>= ctz_bits[v & ctz_mask];
    while ((v & 255) == 0) v >>= 8;
    v >>= ctz_bits[v & 255];

    if (u > v) {
        t = v;
        v = u;
        u = t;
    }
    v = v - u;
    } while (v != 0);

    return (long)(u << shift);
}

unsigned rubygcd_b(long x, long y)
{
    unsigned long u, v, t;
    int shift;
    if (x == 0) return y;
    if (y == 0) return x;

    if (x < 0) x = -x;
    if (y < 0) y = -y;

    u = (unsigned long)x;
    v = (unsigned long)y;
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
    u >>= 1;
    v >>= 1;
    }

    //while ((u & ctz_mask) == 0) u >>= ctz_shift_bits;
    //u >>= ctz_bits[u & ctz_mask];
    //while ((u & 255) == 0) u >>= 8;
    //u >>= ctz_bits[u & 255];
     u >>= __builtin_ctz(u);

    do {
    //while ((v & ctz_mask) == 0) v >>= ctz_shift_bits;
    //v >>= ctz_bits[v & ctz_mask];
    //while ((v & 255) == 0) v >>= 8;
    //v >>= ctz_bits[v & 255];
    v >>= __builtin_ctz(v);

    if (u > v) {
        t = v;
        v = u;
        u = t;
    }
    v = v - u;
    } while (v != 0);

    return (long)(u << shift);
}

/// Чуть быстрее __gcd, для int
template<typename T>
inline T gcd(T a, T b)
{
    while(a %=b) if (!(b %= a)) return a;
    return b;
}

unsigned int test(unsigned int offset) {
	const bool XCHG = true;
    WallClockTimer timer;
    int N = 2000;
    cout << "gcd between numbers in [" << offset+1 << " and "
    << offset+N << "]" << endl;
    int ti1 = 0;
    int ti2 = 0;
    int ti3 = 0;
    int ti4 = 0;
    int ti5 = 0;
    int ti6 = 0;
    int ti7 = 0;
    int ti8 = 0;
    int ti9 = 0;
    int ti10 = 0;
    int ti11 = 0;
    int ti12 = 0;
    int ti13 = 0;
    int ti14 = 0;
    int ti15 = 0;
    int ti16 = 0;
    int ti17 = 0;
    int ti18 = 0;
    int ti19 = 0;
    int ti20 = 0;
    int ti21 = 0;
    int ti22 = 0;
    int ti23 = 0;
    int bogus = 0;
    timer.reset();
    for(unsigned int x = 1+offset; x<=N+offset; ++x)
        for(unsigned int y = 1+offset; y<=N+offset; ++y) {
            assert(gcdwikipedia2(x,y)==gcdwikipedia2fast(x,y));
            assert(gcdwikipedia2(x,y)==gcdwikipedia2fastswap(x,y));
            if(XCHG) assert(gcdwikipedia2(x,y)==gcdwikipedia2fastxchg(x,y));
            assert(gcdwikipedia2(x,y)==gcdwikipedia3fast(x,y));
            assert(gcdwikipedia2(x,y)==gcdwikipedia4fast(x,y));
            assert(gcdwikipedia2(x,y)==gcdwikipedia5fast(x,y));
            if(XCHG) assert(gcdwikipedia2(x,y)==gcdwikipedia6fastxchg(x,y));
            assert(gcdwikipedia2(x,y)==gcdwikipedia7fast(x,y));
            assert(gcdwikipedia2(x,y)==gcdwikipedia7fast32(x,y));
            assert(gcdwikipedia2(x,y)==gcd_recursive(x,y));
            assert(gcdwikipedia2(x,y)==gcd_iterative_mod(x,y));
            assert(gcdwikipedia2(x,y)==basicgcd(x,y));
            assert(gcdwikipedia2(x,y)==gcdFranke(x,y));
            assert(gcdwikipedia2(x,y)==rubygcd(x,y));
            assert(gcdwikipedia2(x,y)==gcdwikipedia7fast32_a(x,y));
            assert(gcdwikipedia2(x,y)==gcdwikipedia4fast_a(x,y));
            assert(gcdwikipedia2(x,y)==rubygcd_a(x,y));
            assert(gcdwikipedia2(x,y)==rubygcd_b(x,y));
            assert(gcdwikipedia2(x,y)==gcd(x,y));
            assert(gcdwikipedia2(x,y)==__gcd(x,y));
         }
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  basicgcd(x,y);
    ti1 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia2(x,y);
    ti2 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia2fast(x,y);
    ti3 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcd_recursive(x,y);
    ti4 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcd_iterative_mod(x,y);
    ti5 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdFranke(x,y);
    ti6 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia3fast(x,y);
    ti7 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia4fast(x,y);
    ti8 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia5fast(x,y);
    ti9 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia2fastswap(x,y);
    ti10 += timer.split();
    timer.reset();
    if(XCHG) for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia6fastxchg(x,y);
    ti11 += timer.split();
    timer.reset();
    if(XCHG) for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia2fastxchg(x,y);
    ti12 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia7fast(x,y);
    ti13 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia7fast32(x,y);
    ti14 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  rubygcd(x,y);
    ti15 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia7fast32_a(x,y);
    ti16 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcdwikipedia4fast_a(x,y);
    ti17 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  rubygcd_a(x,y);
    ti18 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  rubygcd_b(x,y);
    ti19 += timer.split();
    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  gcd(x,y);
    ti20 += timer.split();

    timer.reset();
    for(unsigned int x = 1; x<=N; ++x)
        for(unsigned int y = 1; y<=N; ++y)
            bogus +=  __gcd(x,y);
    ti21 += timer.split();

    cout
    << "\n" << "gcdwikipedia7fast32   : " << " time = " << ti14
    << "\n" << "gcdwikipedia4fast     : " << " time = " << ti8
    << "\n" << "gcdFranke             : " << " time = " << ti6
    << "\n" << "gcdwikipedia3fast     : " << " time = " << ti7
    << "\n" << "gcdwikipedia2fastswap : " << " time = " << ti10
    << "\n" << "gcdwikipedia5fast     : " << " time = " << ti9
    << "\n" << "gcdwikipedia7fast     : " << " time = " << ti13
    << "\n" << "gcdwikipedia2fast     : " << " time = " << ti3
    << "\n" << "gcdwikipedia6fastxchg : " << " time = " << ti11
    << "\n" << "gcdwikipedia2fastxchg : " << " time = " << ti12
    << "\n" << "gcd_iterative_mod     : " << " time = " << ti5
    << "\n" << "gcd_recursive         : " << " time = " << ti4
    << "\n" << "basicgcd              : " << " time = " << ti1
    << "\n" << "rubygcd               : " << " time = " << ti15
    << "\n" << "gcdwikipedia2         : " << " time = " << ti2
    << "\n" << "gcdwikipedia7fast32_a : " << " time = " << ti16
    << "\n" << "gcdwikipedia4fast_a   : " << " time = " << ti17
    << "\n" << "rubygcd_a             : " << " time = " << ti18
    << "\n" << "rubygcd_b             : " << " time = " << ti19
    << "\n" << "dorty                 : " << " time = " << ti20
    << "\n" << "__gcd                 : " << " time = " << ti21
    << endl;
    return bogus;
}

int main() {

    assert(sizeof(int)==4);
    unsigned int bogus = 0;
    bogus += test(0);
    bogus += test(1000*1000*1000);
}
