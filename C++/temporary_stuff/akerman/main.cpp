#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <set>

using namespace std;

#define FORCE_INLINE __attribute__((always_inline)) inline

/// важно, чтобы тип unsign позвол€л вместить в себ€ произведение mod*mod. aka избавл€йтесь от переполнени€
template<typename unsign, typename power_type, typename modulus_obj>
FORCE_INLINE unsign modul_pow(unsign num, power_type power, const modulus_obj& mod){
    unsign cur = 1;

    num %= mod;

    for(;power;power >>= 1) {
        if (power & 1) cur = (cur*num) % mod;
        num = num * num % mod;
    }
    return cur;
}

/// a^WHAT == b (mod m)
int dlog (int a, int b, int m) {
	int n = (int) sqrt (m + .0) + 1;
	map<int,int> vals;
	for (int i=n; i>=1; --i)
		vals[ modul_pow (a, i * n, m) ] = i;
	for (int i=0; i<=n; ++i) {
		int cur = (modul_pow (a, i, m) * b) % m;
		if (vals.count(cur)) {
			int ans = vals[cur] * n - i;
			if (ans < m)
				return ans;
		}
	}
	return -1;
}

/// a^WHAT == b (mod m)
int64_t dlog_min (int64_t a, int64_t b, int64_t m) {
	int64_t n = (int64_t) sqrt (m + .0) + 1;

	int64_t min_ = 1001 * 1001 * 1001;
	map<int64_t, set<int64_t> > vals; /// ¬ данном случае стоит заменить сэт на просто инт и использование инта.
	for (int64_t i=n; i>=1; --i)
		vals[ modul_pow (a, i * n, m) ].insert(i);
	for (int64_t i=0; i<=n; ++i) {
		int64_t cur = (modul_pow (a, i, m) * b) % m;
		if (vals.count(cur)) {
			int64_t ans = *(vals[cur].begin()) * n - i;
			//cout << *vals[cur].begin() << endl;
			if (ans < m)
				///return ans;
				min_ = min(min_, ans);
		}
	}
	if (min_ == 1001 * 1001 * 1001)
        return -1;
    return min_;
}

/// a^WHAT == b (mod m)
int64_t dlog_min_2 (int64_t a, int64_t b, int64_t m, int64_t bound) {
	int64_t n = (int64_t) sqrt (m + .0) + 1;

	int64_t min_ = 1001 * 1001 * 1001;
	map<int64_t, set<int64_t> > vals; /// ¬ данном случае стоит заменить сэт на просто инт и использование инта.
	for (int64_t i=n; i>=1; --i)
		vals[ modul_pow (a, i * n, m) ].insert(i);
	for (int64_t i=0; i<=n; ++i) {
		int64_t cur = (modul_pow (a, i, m) * b) % m;
		if (vals.count(cur)) {
			int64_t ans = *(vals[cur].begin()) * n - i;
			//cout << *vals[cur].begin() << endl;
			if (ans < m && ans > bound)
				///return ans;
				min_ = min(min_, ans);
		}
	}
	if (min_ == 1001 * 1001 * 1001)
        return -1;
    return min_;
}

int main() {


    uint64_t a,b,c,m;
    cin >> a >> b >> c >> m;

    uint64_t w = dlog_min_2(a,a,m,1);
    /// a^w === a
    /// a^(w-1) === 1


    if (w == -1 || w >= m){
        cout << "THIS SHOULD BE UNREACHEBLE" << endl;
    }

    ///cout << w << endl;
    /// the only corner case is when b^c === 0 (mod w), but since there is no zero, we could just add w
    /// 900001111 900001813 900002749 900004201

    /// 900003983 900003431 900002641 900000917

    cout << modul_pow(a, modul_pow(b,c,w-1) + (w-1), m);


    ///cout << dlog_min(a,b,m);
    return 0;
}
