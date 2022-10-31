#include <iostream>
#include <cmath>
#include <time.h>

#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}

uint64_t get_nanoseconds() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

class Clock{
    uint64_t p_time = 0;
    public:
    uint64_t temp_val;
    uint64_t copy;
    public:
    uint64_t tick(){
        temp_val = get_nanoseconds();
        copy = p_time;
        p_time = temp_val;
        return temp_val - copy;
    }

    Clock(){
        p_time = get_nanoseconds();
        std::cout << "ini" << std::endl;
    }

};
///uint64_t Clock::temp_val = 0;
///uint64_t Clock::copy = 0;
using namespace std;

bool isPrimeSimple(int n){
    if (n < 2) return false;
    int limit = sqrt(n) + 1;
    for(int i = 2;i<limit;++i){
        if (!(n % i)) return false;
    }
    return true;
}

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19,
23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
263, 269, 271};

bool isPrimePrimes(int n){
    if (n < 2) return false;
    int limit = sqrt(n) + 1;
    for(int i = 0;primes[i]<limit;++i){
        if (!(n % primes[i])) return false;
    }
    return true;
}

bool PrimesMult(int n){
    if (n < 2) return false;
    int limit = sqrt(n) + 1;
    int m;
    for(int i = 0;primes[i]<limit;++i){
        m = n * primes[i];
    }
    return m;
}

/// check factor
#define cf(t) if (!(n%t)){ return (n==t);}

/// check limit
#define cl(t) if (n < t){ return true;}

#define _5c(a,b,c,d,e,l) cf(a) cf(b) cf(c) cf(d) cf(e) cl(l)

/// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97.

bool inlinePcheck(int n){
    if (n < 2) return false;
    _5c(2,3,5,7,11, 169)
    _5c(13,17,19,23,29, 961)
    _5c(31,37,41,43,47, 2809)
    _5c(53,59,61,67,71, 5329)
    _5c(73,79,83,89,97, 10201)
    _5c(101,103,107,109,113, 16129)
    _5c(127,131,137,139,149, 22801)
    _5c(151,157,163,167,173, 32041)
    _5c(179,181,191,193,197, 39601)
    _5c(199,211,223,227,229, 54289)
    _5c(233,239,241,251,257, 69169)
    _5c(263,269,271,277,281, 80089)
    _5c(283,293,307,311,313, 100489)
    _5c(317,331,337,347,349, 124609)
    _5c(353,359,367,373,379, 146689)
    _5c(383,389,397,401,409, 175561)
    _5c(419,421,431,433,439, 196249)
    _5c(443,449,457,461,463, 218089)
    _5c(467,479,487,491,499, 253009)
    _5c(503,509,521,523,541, 299209)
    _5c(547,557,563,569,571, 332929)
    _5c(577,587,593,599,601, 368449)
    _5c(607,613,617,619,631, 410881)
    _5c(641,643,647,653,659, 436921)
    _5c(661,673,677,683,691, 491401)
    _5c(701,709,719,727,733, 546121)
    _5c(739,743,751,757,761, 591361)
    _5c(769,773,787,797,809, 657721)
    _5c(811,821,823,827,829, 703921)
    _5c(839,853,857,859,863, 769129)
    _5c(877,881,883,887,907, 829921)
    _5c(911,919,929,937,941, 896809)
    _5c(947,953,967,971,977, 966289)
    _5c(983,991,997,1009,1013, 1038361)
    _5c(1019,1021,1031,1033,1039, 1100401)
    _5c(1049,1051,1061,1063,1069, 1181569)
    _5c(1087,1091,1093,1097,1103, 1229881)
    _5c(1109,1117,1123,1129,1151, 1329409)
    _5c(1153,1163,1171,1181,1187, 1423249)
    _5c(1193,1201,1213,1217,1223, 1510441)
    _5c(1229,1231,1237,1249,1259, 1630729)
    _5c(1277,1279,1283,1289,1291, 1682209)
    _5c(1297,1301,1303,1307,1319, 1745041)
    _5c(1321,1327,1361,1367,1373, 1907161)
    _5c(1381,1399,1409,1423,1427, 2042041)
    _5c(1429,1433,1439,1447,1451, 2111209)
    _5c(1453,1459,1471,1481,1483, 2211169)
    _5c(1487,1489,1493,1499,1511, 2319529)
    _5c(1523,1531,1543,1549,1553, 2430481)
    _5c(1559,1567,1571,1579,1583, 2550409)
    _5c(1597,1601,1607,1609,1613, 2621161)
    _5c(1619,1621,1627,1637,1657, 2765569)
    _5c(1663,1667,1669,1693,1697, 2886601)
    _5c(1699,1709,1721,1723,1733, 3031081)
    _5c(1741,1747,1753,1759,1777, 3179089)
    return 1;
}
#undef cl
#undef cf
#undef _5c




/// only for int
unsigned int mod_pow(unsigned long long a, unsigned int t, unsigned int mod) {
    unsigned long long r = 1;

    for (; t; t >>= 1, a = (a) * a % mod)
        if (t & 1)
            r = (r) * a % mod;

    return r;
}

int jacobi (int a, int b)
{
	if (a == 0)  return 0;
	if (a == 1)  return 1;
	if (a < 0){
		if ((b & 2) == 0)
			return jacobi (-a, b);
		else
			return - jacobi (-a, b);
	}
	int a1=a,  e=0;
	while ((a1 & 1) == 0)
		a1 >>= 1,  ++e;
	int s;
	if ((e & 1) == 0 || (b & 7) == 1 || (b & 7) == 7)
		s = 1;
	else
		s = -1;
	if ((b & 3) == 3 && (a1 & 3) == 3)
		s = -s;
	if (a1 == 1)
		return s;
	return s * jacobi (b % a1, a1);
}

/// Чуть быстрее __gcd, для int
template<typename T>
inline T gcd(T a, T b)
{
    while(a %=b) if (!(b %= a)) return a;
    return b;
}

bool BPSW(int n, const bool& flag = 1){

    int intsqrt = sqrt(n);
    /// special case for Lucas tests
    if (intsqrt * intsqrt == n)  return false;

	/// Тривиально выше


	int b = 2;
	for (int g; (g = gcd (n, b)) != 1; ++b)
		if (n > g)
			return false;
	int p=0, q=n-1;
	while ((q & 1) == 0)
		++p,  q >>= 1;
	int rem = mod_pow (b, q, n);
	if (rem == 1 || rem == n-1)
		goto LUCAS;
	for (int i=1; i<p; ++i) {
		rem = (rem * 1ll * rem) % n;
		if (rem == n-1) goto LUCAS;
	}
	return false;

    LUCAS:


	int dd=5;
	for (;;) {
		int g = gcd (n, abs(dd));
		if (1<g && g<n)  return false;
		if (jacobi (dd, n) == -1)  break;
		dd = dd<0 ? -dd+2 : -dd-2;
	}
	int lucas_p=1,  lucas_q=(lucas_p*lucas_p-dd)/4;
	int d=n+1,  s=0;
	while ((d & 1) == 0)
		++s,  d>>=1;
	long long u=1, v=lucas_p, u2m=1, v2m=lucas_p, qm=lucas_q, qm2=lucas_q*2, qkd=lucas_q;
	for (int mask=2; mask<=d; mask<<=1) {
		u2m = (u2m * v2m) % n;
		v2m = (v2m * v2m) % n;
		while (v2m < qm2)   v2m += n;
		v2m -= qm2;
		qm = (qm * qm) % n;
		qm2 = qm * 2;
		if (d & mask) {
			long long t1 = (u2m * v) % n,  t2 = (v2m * u) % n,
				t3 = (v2m * v) % n,  t4 = (((u2m * u) % n) * dd) % n;
			u = t1 + t2;
			if (u & 1)  u += n;
			u = (u >> 1) % n;
			v = t3 + t4;
			if (v & 1)  v += n;
			v = (v >> 1) % n;
			qkd = (qkd * qm) % n;
		}
	}
	if (u==0 || v==0)  return true;
	long long qkd2 = qkd*2;
	for (int r=1; r<s; ++r) {
		v = (v * v) % n - qkd2;
		if (v < 0)  v += n;
		if (v < 0)  v += n;
		if (v >= n)  v -= n;
		if (v >= n)  v -= n;
		if (v == 0)  return true;
		if (r < s-1) {
			qkd = (qkd * 1ll * qkd) % n;
			qkd2 = qkd * 2;
		}
	}
	return false;

}

uint16_t bases[]={15591,2018,166,7429,8064,16045,10503,4399,1949,1295,2776,3620,560,3128,5212,
2657,2300,2021,4652,1471,9336,4018,2398,20462,10277,8028,2213,6219,620,3763,4852,5012,3185,
1333,6227,5298,1074,2391,5113,7061,803,1269,3875,422,751,580,4729,10239,746,2951,556,2206,
3778,481,1522,3476,481,2487,3266,5633,488,3373,6441,3344,17,15105,1490,4154,2036,1882,1813,
467,3307,14042,6371,658,1005,903,737,1887,7447,1888,2848,1784,7559,3400,951,13969,4304,177,41,
19875,3110,13221,8726,571,7043,6943,1199,352,6435,165,1169,3315,978,233,3003,2562,2994,10587,
10030,2377,1902,5354,4447,1555,263,27027,2283,305,669,1912,601,6186,429,1930,14873,1784,1661,
524,3577,236,2360,6146,2850,55637,1753,4178,8466,222,2579,2743,2031,2226,2276,374,2132,813,
23788,1610,4422,5159,1725,3597,3366,14336,579,165,1375,10018,12616,9816,1371,536,1867,10864,
857,2206,5788,434,8085,17618,727,3639,1595,4944,2129,2029,8195,8344,6232,9183,8126,1870,3296,
7455,8947,25017,541,19115,368,566,5674,411,522,1027,8215,2050,6544,10049,614,774,2333,3007,
35201,4706,1152,1785,1028,1540,3743,493,4474,2521,26845,8354,864,18915,5465,2447,42,4511,
1660,166,1249,6259,2553,304,272,7286,73,6554,899,2816,5197,13330,7054,2818,3199,811,922,350,
7514,4452,3449,2663,4708,418,1621,1171,3471,88,11345,412,1559,194};

/// http://ceur-ws.org/Vol-1326/020-Forisek.pdf
bool is_SPRP(uint32_t n, uint32_t a) {
    uint32_t d = n-1, s = 0;
    while ((d&1)==0) ++s, d>>=1;
    uint64_t cur = 1, pw = d;
    while (pw) {
        if (pw & 1) cur = (cur*a) % n;
        a = ((uint64_t)a*a) % n;
        pw >>= 1;
    }
    if (cur == 1) return true; /// prob prime
    for (uint32_t r=0; r<s; r++) {
        if (cur == n-1) return true; /// prob prime
        cur = (cur*cur) % n;
    }
return false; /// definately complex
}



bool is_prime_WTF(uint32_t x) {
    if (x==2 || x==3 || x==5 || x==7) return true;
    if (x%2==0 || x%3==0 || x%5==0 || x%7==0) return false;
    if (x<121) return (x>1);
    uint64_t h = x;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) & 255;
    return is_SPRP(x,bases[h]);
}

__attribute__((always_inline))
bool is_SPRP_complex(const uint32_t& n, uint32_t pw, uint64_t a,const uint8_t& cycle) {

    uint64_t cur = 1;
    while (pw) {
        if (pw & 1) cur = (cur*a) % n;
        a = (a*a) % n;
        pw >>= 1;
    }

    if (cur == 1) return false; /// prob prime
    for (unsigned char r=0; r<cycle; ++r) {
        if (cur == n-1) return false; /// prob prime
        cur = (cur*cur) % n;
    }
return true; /// definately complex
}

bool NextGenRabin(uint32_t n){
    if (n < 2) return false;

    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;

    uint32_t d = n-1;

    unsigned char e = __builtin_ctz(d);
    uint32_t pw = (d >>= e);


    static const uint32_t jp[] = {2, 3, 5, 7};
    for(uint32_t tester : jp)
        if (is_SPRP_complex(n,pw,tester,e)) return false;
    return true;
}



/**
       2,147,483,647 - int limit
if n < 2,047, it is enough to test a = 2;
if n < 1,373,653, it is enough to test a = 2 and 3;
if n < 9,080,191, it is enough to test a = 31 and 73;
if n < 25,326,001, it is enough to test a = 2, 3, and 5;
if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7;
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.

*/

/// ctz - count trailing zeros __builtin_ctz

int ctz(int num){
    int ret = 0;
    for ( --num; !(num & 1); ++ret, num >>= 1 );
    return ret;
}

bool check_prime(unsigned int n) {
    /// Китаец сказал, что 2, 3, 5, 7, 11, 13, 17, 19 для ull
    /// 2, 3, 5 - наверное следует использовать для интов, но 2 и 3 заходит для https://vjudge.net/problem/SPOJ-PRIME1
    static const int jp[] = {2, 3, 5, 7};

    if (n < 2)
        return false;


    if (n % 2 == 0)
        return n == 2;

    if (n % 3 == 0)
        return n == 3;

    if (n % 5 == 0)
        return n == 5;

    if (n % 7 == 0)
        return n == 7;


    int x, y;

    int r = n - 1;
    int e = __builtin_ctz(r);
    r >>= e;

    for (int p : jp) {
        x = mod_pow(p, r, n);

        for (int t = 0; t < e && x > 1; ++t) {
            y = (unsigned long long)x * x % n;

            if (y == 1 && x != n - 1)
                return false;

            x = y;

        }

        if (x != 1)
            return false;
    }

    return true;
}



bool miller_rabin (int n) {
	int b = 2;
	for (int g; (g = gcd (n, b)) != 1; ++b)
		if (n > g)
			return false;
	int p=0, q=n-1;
	while ((q & 1) == 0)
		++p,  q >>= 1;
	int rem = mod_pow (b, q, n);
	if (rem == 1 || rem == n-1)
		return true;
	for (int i=1; i<p; ++i) {
		rem = (rem * 1ll * rem) % n;
		if (rem == n-1)  return true;
	}
	return false;
}

///#include <intrin.h>



int main()
{

    cout << miller_rabin(67777) << endl;
    /*
    const int mnogo = 10000000;
    bool* Sieve = new bool[mnogo];
    for(int i = 0;i< mnogo;++i){
        Sieve[i] = 1;
    }

    string out = "_5c(";
    int cou = 0;

    for(int start = 2; 1; ++start){
        if (Sieve[start]){
            for(int num = start * 2; num < mnogo; num += start){ Sieve[num] = 0;}
            ++cou;
            out += to_str(start);
            if ( cou == 5){

                int lim;
                for(lim = start; 1; ++lim){
                    if ( Sieve[lim] != isPrimeSimple(lim)) break;
                }

                cout << out <<", "<< to_str(lim) <<")" << endl;
                cou = 0;
                out = "_5c(";
            }else{
                out += ",";
            }

        }

    }
    */


    Clock cl;
    cl.tick();

    const int itterations = 1000000;


    for(int i = 0;i<itterations;++i){
        check_prime(67777);
    }

    cout << double(cl.tick()) / itterations << " ns - Deter MR (2,3,5,7)" << endl;

    for(int i = 0;i<itterations;++i){
        inlinePcheck(67777);
    }



    cout << double(cl.tick()) / itterations << " ns - cool method" << endl;

    for(int i = 0;i<itterations;++i){
        BPSW(67777);
    }

    cout << double(cl.tick()) / itterations << " ns - BPSW" << endl;

    for(int i = 0;i<itterations;++i){
        NextGenRabin(67777);
    }

    cout << double(cl.tick()) / itterations << " ns - NGR" << endl;

    for(int i = 0;i<itterations;++i){
        is_prime_WTF(67777);
    }

    cout << double(cl.tick()) / itterations << " ns - WTF" << endl;





    cout << "checked " << endl;

    for(int i = 0;i<itterations;++i){
        inlinePcheck( 2147483647);
    }



    cout << double(cl.tick()) / itterations << " ns - cool method" << endl;



    for(int i = 0;i<itterations;++i){
        is_prime_WTF(2147483647);
    }

    cout << double(cl.tick()) / itterations << " ns - WTF" << endl;


    for(int i = 0;i<itterations;++i){
        check_prime(2147483647);
    }

    cout << double(cl.tick()) / itterations << " ns - Deter MR (2,3,5,7)" << endl;

    for(int i = 0;i<itterations;++i){
        BPSW(2147483647);
    }

    cout << double(cl.tick()) / itterations << " ns - BPSW" << endl;

    for(int i = 0;i<itterations;++i){
        NextGenRabin(2147483647);
    }

    cout << double(cl.tick()) / itterations << " ns - NGR" << endl;

    for(int i = 0;i<1000000;++i){
        bool IPS = isPrimeSimple(i);
        ///bool IPP = isPrimePrimes(i);
        ///bool DMR = isPrimePrimes(i); /// deter Miller Rabin
        bool IPC = inlinePcheck(i);
        if ( !(IPS == IPC)){
            cout << i << " " << IPS << " " << IPC<< endl;
        }
    }


    cout << "Hello world!" << endl;
    return 0;
}
