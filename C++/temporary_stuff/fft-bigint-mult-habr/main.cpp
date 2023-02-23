#include <algorithm>
#include <cstdio>
#include <ctime>
#include <vector>
#include <complex>
#include <iostream>
using namespace std;

double M_PI = acos(0) * 2;

typedef complex<double> cd;
typedef vector<cd> vcd;

vcd fft(const vcd &as) {
  int n = as.size();
  int k = 0; // Длина n в битах
  while ((1 << k) < n) k++;
  vector<int> rev(n);
  rev[0] = 0;
  int high1 = -1;
  for (int i = 1; i < n; i++) {
    if ((i & (i - 1)) == 0) // Проверка на степень двойки. Если i ей является, то i-1 будет состоять из кучи единиц.
      high1++;
    rev[i] = rev[i ^ (1 << high1)]; // Переворачиваем остаток
    rev[i] |= (1 << (k - high1 - 1)); // Добавляем старший бит
  }

  vcd roots(n);
  for (int i = 0; i < n; i++) {
    double alpha = 2 * M_PI * i / n;
    roots[i] = cd(cos(alpha), sin(alpha));
  }

  vcd cur(n);
  for (int i = 0; i < n; i++)
    cur[i] = as[rev[i]];

  for (int len = 1; len < n; len <<= 1) {
    vcd ncur(n);
    int rstep = roots.size() / (len * 2);
    for (int pdest = 0; pdest < n;) {
      int p1 = pdest;
      for (int i = 0; i < len; i++) {
        cd val = roots[i * rstep] * cur[p1 + len];
        ncur[pdest] = cur[p1] + val;
        ncur[pdest + len] = cur[p1] - val;
        pdest++, p1++;
      }
      pdest += len;
    }
    cur.swap(ncur);
  }
  return cur;
}

vcd fft_rev(const vcd &as) {
  vcd res = fft(as);
  for (int i = 0; i < (int)res.size(); i++) res[i] /= as.size();
  reverse(res.begin() + 1, res.end());
  return res;
}

int main() {

    string a_s,b_s;
    cin >> a_s >> b_s;



    vcd a, b; // Многочлены
    // Чтение многочленов

    a.resize(a_s.size());
    b.resize(b_s.size());

    for(int i = 0; i < a_s.size(); ++i){
        a[i] = a_s[a_s.size() - 1 - i] - '0';
        cout << a[i] << endl;
    }

    for(int i = 0; i < b_s.size(); ++i){
        b[i] = b_s[b_s.size() - 1 - i] - '0';
        cout << b[i] << endl;
    }
    cout << "here" << endl;
    vcd a_vals = fft(a);
    cout << "here" << endl;
    vcd b_vals = fft(b);
    cout << "here" << endl;
    vcd c_vals( max(a_vals.size(), b_vals.size()) );
    cout << "here" << endl;
    for (int i = 0; i < a_vals.size(); i++)
        c_vals[i] = a_vals[i] * b_vals[i];

    vcd c = fft_rev(c_vals);

    c.resize(c.size() + 3);

    // Вывод ответа
    string ans = "";
    for(int i = 0; i < c.size() ; ++i ){
        long long value =  (c[i].real() +0.5);
        ans += value % 10 + '0';
        c[i+1] += value/10;
    }

    int last = c.size();
    while( c[last].real() >= 1  ){
        long long value = ((long long)(c[last].real()));
        ans += value % 10 + '0';
        c[last+1] += value/10;
        ++last;
    }

    cout << ans;

    return 0;
}
