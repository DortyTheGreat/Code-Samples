
//#pragma GCC optimize("Ofast,unroll-loops")
///#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>

#define align 64

using namespace std;

/*

6 (vs 3)
for (size_t i = 0; i < NMAX; ++i) {
            int carry = 0;
            for (size_t j = 0; j < NMAX || carry != 0; ++j) {
                long long cur = c[i + j] +
                    a[i] * 1LL * (j < NMAX ? b[j] : 0) + carry;
                c[i + j] = static_cast<int>(cur % BASE);
                carry = static_cast<int>(cur / BASE);
            }
        }


 for (int i = 0; i < NMAX; ++i) {
            int carry = 0;
            for (int j = 0; j < NMAX || carry != 0; ++j) {
                long long cur = c[i + j] +
                    a[i] * 1LL * (j < NMAX ? b[j] : 0) + carry;
                c[i + j] = (cur % BASE);
                carry = (cur / BASE);
            }
        }


for (int i = 0; i < NMAX; ++i) {
            int carry = 0;
            for (int j = 0; j < NMAX; ++j) {
                ll& pts = c[i + j];
                pts += a[i]*b[i];
                if (pts >= BASE){
                    pts -= BASE;
                    ++pts;
                }
            }
        }

3.6 <- good time!
for (int i = 0; i < NMAX; ++i) {
            int carry = 0;
            for (int j = 0; j < NMAX; ++j) {
                ll& pts = c[i + j];
                pts += a[i]*b[i];
                if (pts >= BASE){
                    pts -= BASE;
                    ++c[i+j+1];
                }
            }
        }

*/

namespace {
    template<int n, typename T>
    void mult(const T *__restrict a, const T *__restrict b, T *__restrict res) {
        if (n <= 4) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    res[i + j] += a[i] * b[j];
                }
            }
        } else {
            const int mid = n / 2;
            alignas(align) T* btmp = new T[n], E[n] = {};
            auto atmp = btmp + mid;
            for (int i = 0; i < mid; i++) {
                atmp[i] = a[i] + a[i + mid];
                btmp[i] = b[i] + b[i + mid];
            }
            mult<mid>(atmp, btmp, E);
            mult<mid>(a + 0, b + 0, res);
            mult<mid>(a + mid, b + mid, res + n);
            for (int i = 0; i < mid; i++) {
                const auto tmp = res[i + mid];
                res[i + mid] += E[i] - res[i] - res[i + 2 * mid];
                res[i + 2 * mid] += E[i + mid] - tmp - res[i + 3 * mid];
            }
        }
    }
}

using ll = long long;

const int BASE = 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    const int NMAX = 1 << 10;
    const int sz_2 = NMAX * 2;
    ll *a = new ll[NMAX];
    ll *b = new ll[NMAX];
    ll *c = new ll[sz_2];
    for (int i = 0; i < NMAX; i++){
            a[i] = b[i] = 10;
            c[2*i] = 0;
            c[2 * i + 1] = 0;
    }



    for(int k = 0;k<1000;++k){
        c = new ll[sz_2];
        /*
        for (int i = 0; i < NMAX; ++i) {
            for (int j = 0; j < NMAX; ++j) {
                ll& pts = c[i + j];
                pts += a[i]*b[i];
                if (pts >= BASE){
                    pts -= BASE;
                    ++c[i+j+1];
                }
            }
        }
        */

        mult<NMAX>(a,b,c);
    }
    ll sum = 0;

    for (int i = 0; i < 2 * NMAX; i++){
        cout << c[i] << endl;
        sum += c[i];
    }
    std::cout << sum << std::endl;
    return 0;
}
