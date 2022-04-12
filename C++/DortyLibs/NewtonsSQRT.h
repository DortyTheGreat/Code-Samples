

template <typename T>
T sqrt(T n) {

  T x = 10;
  ///x = x.pow(a.length() / 2 + 1); <- initial guess
  T last = 0;
  int iter = 0;
  while (last != x) {
    last = x;
    x = (x + n / x) / 2;
    cout << last - x << endl;
    ++iter;
  }
  cout << iter << endl;
  return x;
}
