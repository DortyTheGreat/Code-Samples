/// src : https://rosettacode.org/wiki/Fast_Fourier_transform#C

#include <complex>
#include <iostream>
#include <valarray>
using namespace std;
#include <vector>
#include <complex>
#include <complex.h>

const double PI = 3.141592653589793238460;

void _fft(complex<double> buf[], complex<double> out[], int n, int step)
{
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);

        complex<double> omega = std::polar(1.0, -2 * PI / n);
        complex<double> omega_power = 1;
		for (int i = 0; i < n; i += 2 * step) {
			complex<double> t = omega_power * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
			omega_power *= omega;
		}
	}
}

void _ifft(complex<double> buf[], complex<double> out[], int n, int step)
{
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);

        complex<double> omega = std::polar(1.0, 2 * PI /  ((double)(n)) ) / (double)n;
        complex<double> omega_power = 1;
		for (int i = 0; i < n; i += 2 * step) {
			complex<double> t = omega_power * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
			omega_power *= omega;
		}
	}
}

void fft(vector<complex<double>>& vc )
{
	vector<complex<double>> out = vc;


	_fft(vc.data(), out.data(), vc.size(), 1);
}

void ifft(vector<complex<double>>& vc )
{
	vector<complex<double>> out = vc;


	_ifft(vc.data(), out.data(), vc.size(), 1);
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    string a_s,b_s;
    cin >> a_s >> b_s;


    int alen = a_s.size(), blen = b_s.size();
    int resn = alen + blen;	// size of the resulting array
    int s = 0, i;

    while ((1 << s) < resn) s++;	// n = 2^s
    int n = 1 << s;	// round up the the nearest power of two

    vector<complex<double>> a, b; // Многочлены
    // Чтение многочленов

    a.resize(n);
    b.resize(n);

    for(int i = 0; i < a_s.size(); ++i){
        a[i] = a_s[a_s.size() - 1 - i] - '0';
        ///cout << a[i] << endl;
    }

    for(int i = 0; i < b_s.size(); ++i){
        b[i] = b_s[b_s.size() - 1 - i] - '0';
        ///cout << b[i] << endl;
    }




    // forward fft
    fft(a);
    fft(b);

    for(int i = 0; i < n; ++i){
        a[i] *= b[i];
    }

    // inverse fft
    ifft(a);



    // Вывод ответа
    string ans = "";
    for(int i = 0; i < n ; ++i ){
        long long value =  (a[i].real() +0.5);
        ans += value % 10 + '0';
        a[i+1] += value/10;
    }

    bool flag = 0;
    for(int i = ans.size() - 1; i > -1; --i){
        ///cout << "i : " << i << " " << ans[i] << endl;
        if (flag){
            cout << ans[i];
        }else{
            if (ans[i] != '0'){
                flag = 1;
                cout << ans[i];
            }
        }
    }
    if (flag == 0){
        cout << 0;
    }



    return 0;
}
