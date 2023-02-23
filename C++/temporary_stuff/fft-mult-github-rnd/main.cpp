

/// src: https://gist.github.com/agrafix/aa49c17cd32c8ba63b6a7cb8dce8b0bd

#include <complex>
#include <iostream>
#include <valarray>
using namespace std;
#include <vector>
#include <complex>
#include <complex.h>

const double PI = 3.141592653589793238460;

/**
   This computes an in-place complex-to-complex FFT
   x and y are the real and imaginary arrays of 2^m points.
   dir =  1 gives forward transform
   dir = -1 gives reverse transform
*/

/// m - power of 2, n - number (aka m=5, n=32)
inline void FFT(bool inverse,long m,long n,double *x,double *y)
{
    long i,i1,j,k,i2,l,l1,l2;
    double c1,c2,tx,ty,t1,t2,u1,u2,z;



    /* Do the bit reversal */
    i2 = n >> 1;
    j = 0;
    for (i=0;i<n-1;i++) {
        if (i < j) {
            swap(x[i],x[j]);
            swap(y[i],y[j]);
        }
        k = i2;
        while (k <= j) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }

    /* Compute the FFT */
    c1 = -1.0;
    c2 = 0.0;
    l2 = 1;
    for (l=0;l<m;l++) {
        l1 = l2;
        l2 <<= 1;
        u1 = 1.0;
        u2 = 0.0;
        for (j=0;j<l1;j++) {
            for (i=j;i<n;i+=l2) {
                i1 = i + l1;
                t1 = u1 * x[i1] - u2 * y[i1];
                t2 = u1 * y[i1] + u2 * x[i1];
                x[i1] = x[i] - t1;
                y[i1] = y[i] - t2;
                x[i] += t1;
                y[i] += t2;
            }
            z =  u1 * c1 - u2 * c2;
            u2 = u1 * c2 + u2 * c1;
            u1 = z;
        }
        c2 = sqrt((1.0 - c1) / 2.0);
        if (inverse)
            c2 = -c2;
        c1 = sqrt((1.0 + c1) / 2.0);
    }

    /* Scaling for forward transform */
    double n_1 = (1 / (double(n)));
    if (inverse) {
        for (i=0;i<n;i++) {
            x[i] *= n_1;
            y[i] *= n_1 ;
        }
    }
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

    vector<double> a, b; // Многочлены
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



    double *a_imag = new double[n]{0};
    double *b_imag = new double[n]{0};


    for(int i = 0; i < n; ++i){
        //cout << a_imag[i] << " " << b_imag[i] << endl;
    }

    // forward fft
    FFT(0,s,n,a.data(), a_imag );
    FFT(0,s,n,b.data(), b_imag);

    for(int i = 0; i < n; ++i){
        double real = a[i]*b[i] - a_imag[i]*b_imag[i];
        a_imag[i] = a_imag[i]*b[i] + b_imag[i]*a[i];
        a[i] = real;
    }

    // inverse fft
    FFT(1,s,n, a.data(), a_imag);



    // Вывод ответа
    string ans = "";
    for(int i = 0; i < n; ++i ){
        long long value =  (a[i] +0.5);
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
