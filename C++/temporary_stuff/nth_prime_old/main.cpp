#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) {fprintf(stderr, __VA_ARGS__);fflush(stderr);}
#else
	#define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

int isqrt(ll n) {
	return sqrtl(n);
}

vector<int> smalls;
vector<int> roughs;
vector<ll> larges;
vector<bool> skip;

void init(const ll N){

	const int v = isqrt(N);
	int s = (v + 1) / 2;
	smalls = vector<int>(s);
	for (int i = 1; i < s; i++) smalls[i] = i;
	roughs = vector<int>(s);
	for (int i = 0; i < s; i++) roughs[i] = 2 * i + 1;
	larges = vector<ll>(s);
	for (int i = 0; i < s; i++) larges[i] = (N / (2 * i + 1) - 1) / 2;
	skip = vector<bool>(v + 1);

	const auto divide = [](ll n, ll d) -> int { return (double)n / d;};
	const auto half = [](int n) -> int { return (n - 1) >> 1;};
	int pc = 0;
	for (int p = 3; p <= v; p += 2) if (!skip[p]) {
		int q = p * p;
		if ((ll)q * q > N) break;
		skip[p] = true;
		for (int i = q; i <= v; i += 2 * p) skip[i] = true;
		int ns = 0;
		for (int k = 0; k < s; k++) {
			int i = roughs[k];
			if (skip[i]) continue;
			ll d = (ll)i * p;
			larges[ns] = larges[k] - (d <= v ? larges[smalls[d >> 1] - pc] : smalls[half(divide(N, d))]) + pc;
			roughs[ns++] = i;
		}
		s = ns;
		for (int i = half(v), j = ((v / p) - 1) | 1; j >= p; j -= 2) {
			int c = smalls[j >> 1] - pc;
			for (int e = (j * p) >> 1; i >= e; i--) smalls[i] -= c;
		}
		pc++;
	}

}

ll prime_pi(const ll N) {


	const auto divide = [](ll n, ll d) -> int { return (double)n / d;};
	const auto half = [](int n) -> int { return (n - 1) >> 1;};
	int pc = 0;
	for (int p = 3; p <= v; p += 2) if (!skip[p]) {
		int q = p * p;
		if ((ll)q * q > N) break;
		skip[p] = true;
		for (int i = q; i <= v; i += 2 * p) skip[i] = true;
		int ns = 0;
		for (int k = 0; k < s; k++) {
			int i = roughs[k];
			if (skip[i]) continue;
			ll d = (ll)i * p;
			larges[ns] = larges[k] - (d <= v ? larges[smalls[d >> 1] - pc] : smalls[half(divide(N, d))]) + pc;
			roughs[ns++] = i;
		}
		s = ns;
		for (int i = half(v), j = ((v / p) - 1) | 1; j >= p; j -= 2) {
			int c = smalls[j >> 1] - pc;
			for (int e = (j * p) >> 1; i >= e; i--) smalls[i] -= c;
		}
		pc++;
	}
	larges[0] += (ll)(s + 2 * (pc - 1)) * (s - 1) / 2;
	for (int k = 1; k < s; k++) larges[0] -= larges[k];
	for (int l = 1; l < s; l++) {
		ll q = roughs[l];
		ll M = N / q;
		int e = smalls[half(M / q)] - pc;
		if (e < l + 1) break;
		ll t = 0;
		for (int k = l + 1; k <= e; k++)
			t += smalls[half(divide(M, roughs[k]))];
		larges[0] += t - (ll)(e - l) * (pc + l - 1);
	}
	return larges[0] + 1;
}

ll getLn(ll n){
	return log(n);
}


int main(){

	ll n,m;
	cin >> n;

	ll l = n * getLn(n) + n*(getLn(getLn(n))-.6);

	ll u =  n * getLn(n) + n*(getLn(getLn(n))+.9);

	//cout << l << "   " << u <<endl;
	while(l != u){
		m = l + (u - l) /2;
		if(prime_pi(m) >= n)u = m;
		else l = m + 1;
		//cout<<"m = " << m << endl;
	}
	if(n==1)puts("2");
	else if(n==2)puts("3");
	else{
	if(m%2==0)m+=1;

	cout << m ;
	}
}
