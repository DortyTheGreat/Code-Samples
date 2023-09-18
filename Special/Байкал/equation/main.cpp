#include <iostream>

using namespace std;

/// base^e % mod
unsigned long long powmod_64(unsigned long long base, unsigned long long e, unsigned long long mod) {
    unsigned long long result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (__uint128_t)result * base % mod;
        base = (__uint128_t)base * base % mod;
        e >>= 1;
    }
    return result;
}

#include <map>

#include <cmath>
#include <iostream>
using namespace std;

#include <vector>
#define VI vector<int64_t>
#define int int64_t
#define double long double
double PI = acos(0) * 2;



class complex
{
public:
    double a, b;
	complex() {a = 0.0; b = 0.0;}
	complex(double na, double nb) {a = na; b = nb;}
	const complex operator+(const complex &c) const
		{return complex(a + c.a, b + c.b);}
	const complex operator-(const complex &c) const
		{return complex(a - c.a, b - c.b);}
	const complex operator*(const complex &c) const
		{return complex(a*c.a - b*c.b, a*c.b + b*c.a);}
	double magnitude() {return sqrt(a*a+b*b);}
	void print() {printf("(%.3f %.3f)\n", a, b);}
};

class FFT
{
public:
	vector<complex> data;
	vector<complex> roots;
	VI rev;
	int s, n;

	void setSize(int ns)
	{
		s = ns;
		n = (1 << s);
		int i, j;
		rev = VI(n);
		data = vector<complex> (n);
		roots = vector<complex> (n+1);
		for (i = 0; i < n; i++)
			for (j = 0; j < s; j++)
				if ((i & (1 << j)) != 0)
					rev[i] += (1 << (s-j-1));
		roots[0] = complex(1, 0);
		complex mult = complex(cos(2*PI/n), sin(2*PI/n));
		for (i = 1; i <= n; i++)
			roots[i] = roots[i-1] * mult;
	}

	void bitReverse(vector<complex> &array)
	{
		vector<complex> temp(n);
		int i;
		for (i = 0; i < n; i++)
			temp[i] = array[rev[i]];
		for (i = 0; i < n; i++)
			array[i] = temp[i];
	}

	void transform(bool inverse = false)
	{
		bitReverse(data);
		int i, j, k;
		for (i = 1; i <= s; i++) {
			int m = (1 << i), md2 = m / 2;
			int start = 0, increment = (1 << (s-i));
			if (inverse) {
				start = n;
				increment *= -1;
			}
			complex t, u;
			for (k = 0; k < n; k += m) {
				int index = start;
				for (j = k; j < md2+k; j++) {
					t = roots[index] * data[j+md2];
					index += increment;
					data[j+md2] = data[j] - t;
					data[j] = data[j] + t;
				}
			}
		}
		if (inverse)
			for (i = 0; i < n; i++) {
				data[i].a /= n;
				data[i].b /= n;
			}
	}

	static VI convolution(VI &a)
	{
		int alen = a.size();
		int resn = alen + alen - 1;	// size of the resulting array
		int s = 0, i;
		while ((1 << s) < resn) s++;	// n = 2^s
		int n = 1 << s;	// round up the the nearest power of two

		FFT pga;
		pga.setSize(s);	// fill and transform first array
		for (i = 0; i < alen; i++) pga.data[i] = complex(a[i], 0);
		for (i = alen; i < n; i++)	pga.data[i] = complex(0, 0);
		pga.transform();

		for (i = 0; i < n; i++)	pga.data[i] = pga.data[i] * pga.data[i];
		pga.transform(true);	// inverse transform
		VI result = VI (resn);	// round to nearest integer
		for (i = 0; i < resn; i++)	result[i] = (int64_t) (pga.data[i].a + 0.5);
        /**
		int actualSize = resn - 1;	// find proper size of array
		while (result[actualSize] == 0)
			actualSize--;
		if (actualSize < 0) actualSize = 0;
		result.resize(actualSize+1);
		*/
		return result;
	}
};




#undef VI



signed main()
{

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);


    int n = 13*2;
    int m = 13*2*5;
    cin >> n >> m;

    const int NMAX = (1 << 20);
    vector<int64_t> a(NMAX);
    //cout << "here" << endl;

    for(int i = 0; i < NMAX; ++i){
        a[i] = 0;
    }

    map<int,int> mp;
    for(int i = 1; i < m; ++i){

        /**if (powmod_64(i,n,m) != 0)*/ a[powmod_64(i,n,m)]++;
        //cout << powmod_64(i,n,m) << " ";
    }

    cout << endl;
    vector<int64_t> c = FFT::convolution(a);


    for(int i = 0; i < m; ++i){
        //cout << a[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < m; ++i){
        //cout << c[i] + c[i + m] << " ";
    }

    cout << endl;

    for(int i = 0; i < 2*m; ++i){
        //cout << c[i] << " ";
    }

    cout << endl;

    /**
    int64_t sum = 0;
    for (int i = 1; i < m; i++){
        int64_t val = ((c[i] + c[i + m]) + 1) / 2;
        sum += val;
        ///sum %= m;
    }
    **/


    int64_t sum = 0;
    for (int i = 0; i < m; i++){

        if (i % 2 == 1){
            sum += a[i] * ((c[i] + 1 )/2); /// нет кейсов с повторениями ????
        }else{
            sum += a[i] * (c[i] - (c[i] - a[i/2])/2 );
        }


        //cout << sum << endl;

        if ( (i + m) % 2 == 1 ){
            sum += a[i] * ((c[i+m] + 1 )/2); /// нет кейсов с повторениями ????
        }else{
            sum += a[i] * (c[i+m] - (c[i+m] - a[(i+m)/2])/2 );
        }

        //cout << sum << endl;

        ///int64_t val = a[i] * (c[i] + c[i + m] );
        ///int64_t val = (((c[i] + c[i + m]) + 1) / 2) * a[i];
        ///sum += val;
        ///sum %= m;
    }

    cout << sum;

    cout << endl << endl;
    for(const auto& it: mp){
        ///cout << it.first << " " << it.second << endl;
    }





    return 0;
}
