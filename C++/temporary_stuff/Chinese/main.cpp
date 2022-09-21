#include <cstring>
#include <cstdio>
#include <cmath>
#include <utility>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <stdint.h>
typedef uint64_t u64;
typedef __uint128_t u128;
typedef __int128_t i128;
namespace Timer {
template<class T, class...Args>
std::pair<u64, T> Time(T(*func)(Args...ar), Args...ar) {
    using hrc = std::chrono::high_resolution_clock;
    hrc::time_point start = hrc::now();
    T out = func(ar...);
    return std::pair<u64, T>(u64(std::chrono::duration_cast<std::chrono::nanoseconds>
                                 (hrc::now() - start).count()), out);
}
}
inline u128 getint() {
    u128 ret = 0;
    bool ok = 0, neg = 0;

    for (;;) {
        int c = getchar();

        if (c >= '0' && c <= '9')
            ret = (ret << 3) + ret + ret + c - '0', ok = 1;
        else if (ok)
            return neg ? 0 - ret : ret;
        else if (c == '-')
            neg = 1;
    }
}
void printint(u128 n) {
    const u64 ten18 = u64(1e18);

    if (n >= ten18)
        printf("%llu%018llu", u64(n / ten18), u64(n % ten18));
    else
        printf("%llu", u64(n));
}
#define rep(i,a,n) for (int i=a;i<n;i++)
struct u256 {
    u256() {}
    u256(u128 l, u128 h): lo(l), hi(h) {}
    static u256 mul128(u128 a, u128 b) {
        u64 a_hi = a >> 64, a_lo = u64(a);
        u64 b_hi = b >> 64, b_lo = u64(b);
        u128 p01 = u128(a_lo) * b_lo;
        u128 p12 = u128(a_hi) * b_lo + u64(p01 >> 64);
        u64 t_hi = p12 >> 64, t_lo = p12;
        p12 = u128(a_lo) * b_hi + t_lo;
        u128 p23 = u128(a_hi) * b_hi + u64(p12 >> 64) + t_hi;
        return u256(u64(p01) | (p12 << 64), p23);
    }
    u128 lo, hi;
};
struct Mont {
    Mont(u128 n): mod(n) {
        inv = n;
        rep(i, 0, 6) inv *= 2 - n * inv;
        r2 = -n % n;

        rep(i, 0, 4) if ((r2 <<= 1) >= mod)
            r2 -= mod;

        rep(i, 0, 5) r2 = mul(r2, r2);
    }
    u128 reduce(u256 x) const {
        u128 y = x.hi - u256::mul128(x.lo * inv, mod).hi;
        return i128(y) < 0 ? y + mod : y;
    }
    u128 reduce(u128 x) const {
        return reduce(u256(x, 0));
    }
    u128 init(u128 n) const {
        return reduce(u256::mul128(n, r2));
    }
    u128 mul(u128 a, u128 b) const {
        return reduce(u256::mul128(a, b));
    }
    u128 mod, inv, r2;
};
// the Min-25 montgomery form manipulator
u128 ctz(u128 x) {
    int a = __builtin_ctzll(u64(x >> 64)) + 64, b = __builtin_ctzll(u64(x));
    return u64(x) ? b : a;
}
u128 gcd(u128 a, u128 b) {
    if (b == 0)
        return a;

    int shift = ctz(a | b);
    b >>= ctz(b);

    while (a) {
        a >>= ctz(a);

        if (a < b)
            std::swap(a, b);

        a -= b;
    }

    return b << shift;
}
i128 invert(i128 a, i128 b) {
    if (!a || !b)
        return 0;

    //  putchar(':'),printint(u128(a)),putchar(' '),printint(u128(b)),putchar('\n');
    bool truth = 0;

    if (a < 0)
        a = -a, truth = 1;

    i128 b_or = b, alpha = 1, beta = 0;

    while (!(a & 1)) {
        if (alpha & 1)
            alpha += b_or;

        alpha >>= 1, a >>= 1;
    }

    if (b > a)
        std::swap(a, b), std::swap(alpha, beta);

    while (b && (a ^ b)) {
        a -= b;
        alpha -= beta;

        while (!(a & 1)) {
            if (alpha & 1)
                alpha += b_or;

            alpha >>= 1, a >>= 1;
        }

        if (b > a)
            std::swap(a, b), std::swap(alpha, beta);
    }

    if (a == b)
        b = 0, alpha -= beta, std::swap(alpha, beta);

    //  putchar(':'),printint(u128(alpha)),putchar(' '),printint(u128(beta)),putchar('\n');
    //  putchar(':'),printint(u128(-alpha)),putchar(' '),printint(u128(-beta)),putchar('\n');
    if (truth)
        alpha = b_or - alpha;

    alpha = alpha % b_or;

    if (alpha < 0)
        alpha += b_or;

    if (a != 1)
        return 0;

    return alpha;
}
//invert and gcd
u64 sqrt_approx(u64 x) {
    u64 approx = sqrt(double(x));
    return (approx + x / approx) >> 1;
}
u64 sqrt(u64 x) {
    u64 approx = sqrt(double(x));
    u64 apt = (approx + x / approx) >> 1;
    approx = apt * apt;

    if (approx > x)
        return apt - 1;

    if (x - approx >= 2 * apt - 1)
        return apt + 1;

    return apt;
}
u128 sqrt(u128 r) {
    if (!(r >> 64))
        return sqrt(u64(r));

    int cnt = (((64 - __builtin_clzll(u64(r >> 64))) + 1) | 1) ^ 1;
    u128 approx = u128(sqrt_approx(u64(r >> cnt))) << (cnt / 2);
    approx = (approx + r / approx) >> 1;
    u128 apt = u128(u64(approx)) * u128(u64(approx));
    return approx - ((r - apt) >> 127);
}
// fast int128 square root
#define ModularManipulate \
    u128 n=Modu->mod; \
    const auto add=[&] (u128 x,u128 y) { return (x+=y)>=n?x-n:x; }; \
    const auto sub=[&] (u128 x,u128 y) { return i128(x-=y)<0?x+n:x; }; \
    const auto mul=[&] (u128 x,u128 y) { return Modu->mul(x,y); }; \
    const auto get=[&] (u128 x)        { return Modu->reduce(x); }; \
    const auto set=[&] (u128 x)        { return Modu->init(x); }; \
    const auto dbl=[&] (u128 x)        { return (x<<=1)>=n?x-n:x; };

u128 invert(u128 *inv, u128 *lis, int len, Mont *Modu) {
    ModularManipulate

    for (int i = 1; i < len; ++i)
        inv[i - 1] = lis[i],
                     lis[i] = mul(lis[i], lis[i - 1]);

    u128 invt = u128(invert(get(lis[len - 1]), n));

    //  printint(get(lis[len-1])),putchar(' '),printint(invt),putchar('\n');
    if (!invt) {
        while (~--len) {
            u128 factor = gcd(lis[len], n);

            if (factor == 1)
                break;

            if (factor < n)
                return factor;
        }

        return 1;
    }

    invt = set(invt);

    for (int i = len - 1; i; --i)
        inv[i] = mul(invt, lis[i - 1]),
                 invt = mul(invt, inv[i - 1]);

    inv[0] = invt;
    return 0;
}
const int maxn = 400;
// invert a list of u128 in parallel, while returning 1 indicates failure, returning 0 indicates inverted,
// returning other indicates successful factorization
struct affine {
    u128 x, y, c;
};

affine tempaff[4][maxn];
u128 tempui[4][maxn];//

u128 Add(affine *p1, affine *p2, int len, Mont *Modu) {
    ModularManipulate
    u128 *inv = tempui[0], *invr = tempui[1];

    for (int i = 0; i < len; ++i)
        inv[i] = sub(p1[i].x, p2[i].x);

    u128 k = invert(invr, inv, len, Modu);

    if (k)
        return k;

    for (int i = 0; i < len; ++i) {
        k = mul(sub(p1[i].y, p2[i].y), invr[i]);
        p2[i].x = sub(sub(mul(k, k), p1[i].x), p2[i].x);
        p2[i].y = sub(mul(k, sub(p1[i].x, p2[i].x)), p1[i].y);
    }

    return 0;
}
u128 Addsub_x(affine *p1, affine *p2, u128 *sum, u128 *dif, int len, Mont *Modu) {
    ModularManipulate
    u128 *inv = tempui[0];

    for (int i = 0; i < len; ++i)
        sum[i] = sub(p2[i].x, p1[i].x);

    u128 k = invert(inv, sum, len, Modu), r;

    if (k)
        return k;

    for (int i = 0; i < len; ++i) {
        k = mul(sub(p2[i].y, p1[i].y), inv[i]);
        r = mul(add(p2[i].y, p1[i].y), inv[i]);
        sum[i] = sub(sub(mul(k, k), p1[i].x), p2[i].x);
        dif[i] = sub(sub(mul(r, r), p1[i].x), p2[i].x);
    }

    return 0;
}
u128 pow(u128 base, u128 exp, Mont *Modu) {
    ModularManipulate
    u128 ca[4];
    ca[0] = 1;
    ca[1] = base;
    ca[2] = mul(base, base), ca[3] = mul(ca[2], base);
    bool f = 0;

    for (int i = 126; i >= 0; i -= 2) {
        if (f)
            ca[0] = mul(ca[0], ca[0]), ca[0] = mul(ca[0], ca[0]);

        int q = (exp >> i) & 3;

        if (q)
            f = 1, ca[0] = mul(ca[0], ca[q]);
    }

    return ca[0];
}
u128 Double(affine *p1, int len, Mont *Modu) {
    ModularManipulate
    u128 *inv = tempui[0], *invr = tempui[1];

    for (int i = 0; i < len; ++i)
        inv[i] = dbl(p1[i].y);

    u128 k = invert(invr, inv, len, Modu);

    if (k)
        return k;

    for (int i = 0; i < len; ++i) {
        u128 r = p1[i].x;
        k = mul(r, r);
        k = mul(add(dbl(k), add(k, p1[i].c)), invr[i]);
        p1[i].x = sub(mul(k, k), dbl(r));
        p1[i].y = sub(mul(k, sub(r, p1[i].x)), p1[i].y);
    }

    return 0;
}
u128 Sub(affine *p1, affine *p2, int len, Mont *Modu) {
    ModularManipulate
    u128 *inv = tempui[0], *invr = tempui[1];

    for (int i = 0; i < len; ++i)
        inv[i] = sub(p2[i].x, p1[i].x);

    u128 k = invert(invr, inv, len, Modu);

    if (k)
        return k;

    for (int i = 0; i < len; ++i) {
        k = mul(add(p1[i].y, p2[i].y), invr[i]);
        p2[i].x = sub(sub(mul(k, k), p1[i].x), p2[i].x);
        p2[i].y = add(mul(k, sub(p1[i].x, p2[i].x)), p1[i].y);
    }

    return 0;
}
u128 NAFConv(u64 E) { //NAF with a leading 01. So use with E<2^63
    u128 res = 1;

    while (E) {
        if (E & 1)
            res = (res << 2) | (E & 3), E -= 2 - (E & 3);
        else
            res <<= 2;

        E >>= 1;
    }

    return res;
}
#define prr(x) printpoints(x,len,Modu)
void printpoints(affine *af, int len, Mont *Modu) {
    ModularManipulate
    printf("Count:\n%d\n[", len);

    for (int i = 0; i < len; ++i) {
        putchar('[');
        printint(get(af[i].x)), putchar(','),
                 printint(get(af[i].y)), putchar(','),
                 printint(get(af[i].c)), puts("],");
    }

    puts("]");
}
u128 FastMultiply(affine *p1, u64 d, int len, Mont *Modu) {
    if (d == 1)
        return 0;

    u128 Na = NAFConv(d);
    affine *tem = tempaff[0];
    std::copy(p1, p1 + len, tem);
    Na >>= 2;

    //  prr(p1);
    while (Na != 1) {
        int op = Na & 3;
        u128 k = Double(p1, len, Modu);

        //      puts("*2");
        //      prr(p1);
        if (k)
            return k;

        if (op == 1)
            k = Add(tem, p1, len, Modu); //,puts("+1"),prr(p1),prr(tem);
        else if (op == 3)
            k = Sub(tem, p1, len, Modu); //,puts("-1"),prr(p1),prr(tem);

        if (k)
            return k;

        Na >>= 2;
    }

    return 0;
}
u128 InitPoints(u128 *param, affine *points, int len, Mont *Modu) {
    ModularManipulate
    u128 five = set(5), two = set(2), one = set(1);

    for (int cn = 0; cn < len; ++cn) {
        u128 sigma = param[cn];
        u128 u = sub(mul(sigma, sigma), five);
        u128 v = dbl(dbl(sigma));
        u128 i = mul(mul(u, u), dbl(dbl(mul(u, v))));
        points[cn].x = u;
        points[cn].y = v;
        points[cn].c = i;
        param[cn] = mul(i, v);
    }

    u128 *inv = tempui[0];
    u128 ret = invert(inv, param, len, Modu);

    if (ret)
        return ret;

    for (int j = 0; j < len; ++j) {
        u128 u = points[j].x, v = points[j].y, i = points[j].c;
        u128 in = inv[j];
        u128 t1 = sub(v, u), t2 = add(dbl(u), add(u, v));
        t1 = mul(mul(t1, t1), t1);
        u128 a = sub(mul(mul(t1, t2), in), two);
        t1 = mul(u, mul(i, in));
        u128 x0 = mul(t1, mul(t1, t1));
        u128 b = mul(add(x0, a), x0);
        b = mul(add(b, one), x0);
        x0 = mul(b, x0);
        u128 y0 = mul(b, b);
        t1 = get(a);

        while (t1 % 3)
            t1 += n;

        t1 = set(t1 / 3);
        x0 = add(x0, mul(t1, b));
        t2 = mul(y0, sub(one, mul(t1, a)));
        points[j].x = x0;
        points[j].y = y0;
        points[j].c = t2;
    }

    return 0;
}
namespace Sieve {
typedef unsigned int u32;
typedef unsigned long long ull;
const char pr60[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
const char masks[][4] = {
    {3, 7, 11, 13},
    {3, 17, 19, 23},
    {2, 29, 31},
    {2, 37, 41},
    {2, 43, 47},
    {2, 53, 59}
};
const u32 segsize = 65536;
void Apply_mask(u32 *a, u32 *b, u32 l1, u32 l2) {
    u32 t = 0;

    for (u32 q = 0, r = l1 / l2; q < r; ++q)
        for (u32 i = 0; i < l2; ++i)
            a[t++] |= b[i];

    for (u32 i = 0; t < l1; ++i)
        a[t++] |= b[i];
}
void Gen_mask_sub(u32 *a, u32 l1, u32 b) {
    u32 st = b >> 1, rt = 0;

    while (rt < l1) {
        a[rt] |= 1 << st;
        st += b;

        if (st >= 30)
            st -= 30, ++rt;

        if (st >= 30)
            st -= 30, ++rt;
    }
}
void PrintMask(u32 *a, u32 len) {
    printf("Mask of len %u\n", len * 60);

    for (u32 i = 0; i < len; ++i) {
        for (u32 j = 0; j < 30; ++j)
            if ((a[i] & (1 << j)))
                printf("%llu\n", i * 60ull + j * 2ull + 1ull);
    }
}
u32 Gen_mask(u32 *a, int id) {
    int len = masks[id][0];
    u32 ll = 1;

    for (int i = 1; i <= len; ++i)
        ll *= masks[id][i];

    memset(a, 0, 4 * ll);

    for (int i = 1; i <= len; ++i)
        Gen_mask_sub(a, ll, masks[id][i]);

    //  PrintMask(a,ll);
    return ll;
}
const u32 mask = 0x1a4b3496;
const u32 pr60_m = 0xdb4b3491;
u32 pr[10000][4], prl;
std::vector<u32> main(ull ma) {
    ull tma, tmx;
    tma = (ma - 1) / 60 + 1;
    tmx = tma * 60; //upper limit
    u32 *sieve = new u32[tma]; // getting a sieve ready
    u32 *maske = new u32[7429];
    std::fill(sieve, sieve + tma, mask);

    for (int i = 0; i < 6; ++i)
        Apply_mask(sieve, maske, tma, Gen_mask(maske, i));

    ull preseg = std::min(tmx, ull(sqrt(double(ma)) / 60) + 1);
    u32 j = 61;

    for (; ull(j)*j <= preseg * 60; j += 2) {
        u32 v = j / 60, u = (j % 60) >> 1;

        if (!(sieve[v] & (1 << u))) {
            v = j / 30, u = j % 30;
            u32 rt = j * 3 / 60, st = (j * 3 % 60) >> 1;

            while (rt < preseg) {
                sieve[rt] |= 1 << st;
                rt += v;
                st += u;

                if (st >= 30)
                    st -= 30, ++rt;
            }

            pr[prl][0] = v;
            pr[prl][1] = u;
            pr[prl][2] = rt;
            pr[prl][3] = st;
            prl++;
        }
    } // Non-segmented sieve core

    if (preseg == tmx)
        goto end;

    for (u32 segl = preseg; segl < tma; segl += segsize) {
        u32 segr = std::min(segl + segsize, u32(tma));

        for (; ull(j)*j <= segr * 60; j += 2) {
            u32 v = j / 60, u = (j % 60) >> 1;

            if (!(sieve[v] & (1 << u))) {
                v = j / 30, u = j % 30;
                ull t = j * ull(j);
                u32 rt = t / 60, st = t % 60 >> 1;
                pr[prl][0] = v;
                pr[prl][1] = u;
                pr[prl][2] = rt;
                pr[prl][3] = st;
                prl++;
            }
        }

        for (int i = 0; i < prl; ++i) {
            u32 v = pr[i][0], u = pr[i][1], rt = pr[i][2], st = pr[i][3];

            while (rt < segr) {
                sieve[rt] |= 1 << st;
                rt += v;
                st += u;

                if (st >= 30)
                    st -= 30, ++rt;
            }

            pr[i][0] = v;
            pr[i][1] = u;
            pr[i][2] = rt;
            pr[i][3] = st;
        }
    }

end:
    sieve[0] = pr60_m;
    std::vector<u32> ret;
    ret.push_back(2);

    for (u32 i = 0; i < tma; ++i) {
        for (u32 j = 0; j < 30; ++j)
            if (!(sieve[i] & (1 << j)))
                ret.push_back(i * 60 + j * 2 + 1);
    }

    return ret;
}
}
u128 factor(u128 N, int SmoothBound, int curve_count, std::vector<unsigned int> primes) {
    u128 *param = tempui[2];
    Mont Mod(N);
    Mont *Modu = &Mod;
    ModularManipulate

    for (int i = 0; i < curve_count; ++i)
        param[i] = set(48923798 + i);

    affine *plist = tempaff[2];
    u128 ret = InitPoints(param, plist, curve_count, &Mod);

    //  printpoints(plist,curve_count,&Mod);
    if (ret)
        return ret;

    u128 std = u128(1) << 63;
    u64 qbound = u64(sqrt(N));
    u64 rbound = qbound + sqrt(qbound) + 1;
    u64 tot = 1;
    u128 cmp = u128(1) << 60;

    for (int i : primes) {
        if (i > SmoothBound)
            break;

        u64 t = i, g = SmoothBound / i;

        while (t <= g)
            t *= i;

        if (u128(tot)*t < cmp)
            tot *= t;
        else {
            ret = FastMultiply(plist, tot, curve_count, Modu);
            tot = t;

            if (ret)
                return ret;
        }
    }

    if (tot != 1) {
        ret = FastMultiply(plist, tot, curve_count, Modu);

        if (ret)
            return ret;
    }

    return 1;
}
#define _cp(a,b) std::copy(a,a+curve_count,b)
affine pire[100][maxn];
#define _call(Fn,...) ret=Fn(__VA_ARGS__,curve_count,Modu);if(ret)return ret;
u128 factor_twophase(u128 N, int B1, int B2, int curve_count, std::vector<unsigned int> primes,
                     int seed = 48923798) {
    u128 *param = tempui[2];
    Mont Mod(N);
    Mont *Modu = &Mod;
    ModularManipulate

    for (int i = 0; i < curve_count; ++i)
        param[i] = set(seed + i);

    affine *plist = tempaff[2];
    u128 ret;
    _call(InitPoints, param, plist);
    u128 std = u128(1) << 63;
    u64 qbound = u64(sqrt(N));
    u64 rbound = qbound + sqrt(qbound) + 1;
    u64 tot = 1;
    u128 cmp = u128(1) << 60;
    // phase1
    int j = 0, lenp = primes.size();

    for (int i = primes[j]; j < lenp; i = primes[++j]) {
        if (i > B1)
            break;

        u64 t = i, g = B2 / i;

        while (t <= g)
            t *= i;

        if (u128(tot)*t < cmp)
            tot *= t;
        else {
            _call(FastMultiply, plist, tot);
            tot = t;
        }
    }

    if (tot != 1) {
        _call(FastMultiply, plist, tot);
    }

    // phase 2
    _cp(plist, pire[0]);
    _call(Double, pire[0]);
    _cp(pire[0], pire[1]);
    _call(Double, pire[1]);
    int pirep = 2;
    _call(FastMultiply, plist, primes[j++]);

    for (int i = primes[j] - primes[j - 1]; j < lenp; ++j, i = primes[j] - primes[j - 1]) {
        if (primes[j] > B2)
            break;

        while (i > pirep * 2) {
            _cp(pire[pirep - 1], pire[pirep]);
            _call(Add, pire[0], pire[pirep]);
            ++pirep;
        }

        _call(Add, pire[i - 2 >> 1], plist);
    }

    return 1;
}
void Test(u128 N, int SmoothBound, int curve_count, std::vector<unsigned int> primes) {
    u128 *param = tempui[2];
    affine *plist = tempaff[2];
    affine *plist2 = tempaff[3];
    Mont Mod(N);
    Mont *Modu = &Mod;
    ModularManipulate

    for (int i = 0; i < curve_count; ++i)
        param[i] = set(6 + i);

    u128 ret = InitPoints(param, plist, curve_count, &Mod);
    printpoints(plist, curve_count, Modu);
    std::copy(plist, plist + curve_count, plist2);
    Double(plist, curve_count, Modu);
    printpoints(plist, curve_count, Modu);
}

namespace Factor64 {
struct Mont {
    Mont(u64 n): mod(n) {
        inv = n;
        rep(i, 0, 5) inv *= 2 - n * inv;
        r2 = -n % n;

        rep(i, 0, 4) if ((r2 <<= 1) >= mod)
            r2 -= mod;

        rep(i, 0, 4) r2 = mul(r2, r2);
    }
    u64 reduce(u128 x) const {
        u64 y = (x >> 64) - (u128(u64(x) * inv) * mod >> 64);
        return int64_t(y) < 0 ? y + mod : y;
    }
    u64 reduce(u64 x) const {
        return reduce(u128(x));
    }
    u64 init(u64 n) const {
        return reduce(u128(n) * r2);
    }
    u64 mul(u64 a, u64 b) const {
        return reduce(u128(a) * b);
    }
    u64 mod, inv, r2;
};
u64 gcd(u64 a, u64 b) {
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

u64 rho(u64 n) {
    if (!(n & 1))
        return 2;

    Factor64::Mont mont(n);
    auto add = [&](u64 x, u64 y) {
        return (x += y) >= n ? x - n : x;
    };
    auto sub = [&](u64 x, u64 y) {
        return int64_t(x -= y) < 0 ? x + n : x;
    };
    auto mul = [&](u64 x, u64 y) {
        return mont.mul(x, y);
    };
    u64 c = 137;

    while (1) {
        ++c;
        const u64 one = mont.init(1), mc = mont.init(c);
        auto f = [&](u64 x) {
            return add(mul(x, x), mc);
        };
        u64 y = one;
        int cnt = 0;

        for (u64 l = 1;; l <<= 1) {
            u64 x = y;

            for (u64 i = 0; i < l; ++i)
                y = f(y), cnt++;

            u64 p = one;

            for (u64 k = 0; k < l; k += 32) {
                u64 sy = y;

                for (u64 i = 0; i < std::min(u64(32), l - k); i++)
                    y = f(y), p = mul(p, sub(y, x)), cnt++;

                u64 g = gcd(n, p);

                if (g == 1)
                    continue;

                if (g == n) {
                    for (g = 1, y = sy; g == 1;)
                        y = f(y), g = gcd(n, sub(y, x));
                }

                if (g != n) {
                    return g;
                }

                break;
            }

            //          fprintf(stderr,"%llu %d\n",l,cnt);
        }
    }
}
}
int params[2][2] = {
    {2000, 80},
    {5000, 100}
};
int __main() {
    u128 inp = getint();
    u128 p = 1;

    if (inp < (u128(1) << 63))
        p = Factor64::rho(u64(inp));
    else {
        std::vector<unsigned int> pr = Sieve::main(30000);

        if (inp > (u128(1) << 90))
            p = factor_twophase(inp, 2500, 21000, 120, pr);
        else
            p = factor_twophase(inp, 700, 7000, 80, pr);
    }

    u128 q = inp / p;

    if (q < p)
        std::swap(p, q);

    printint(p), putchar(' '), printint(q);
    //  Test(inp,200,1,pr);
    return 0;
}
int main() {
    //  auto x=Timer::Time(__main);
    //  fprintf(stderr,"%.8lfs consumed",double(x.first)/1e9);
    __main();
    return 0;
}
