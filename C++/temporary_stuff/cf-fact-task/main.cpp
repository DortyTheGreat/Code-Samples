#include <iostream>

using namespace std;

const int mod = 1000000271;

//возвращает n-е число Фибоначчи
long long fib(int n)
{
  long long a = 1, ta,
      b = 1, tb,
      c = 1, rc = 0,  tc,
      d = 0, rd = 1;

  while (n)
  {
    if (n & 1)    // Если степень нечетная
    {
      // Умножаем вектор R на матрицу A
      tc = rc;
      rc = (rc*a + rd*c) % mod;
      rd = (tc*b + rd*d) % mod;
    }

    // Умножаем матрицу A на саму себя
    ta = a; tb = b; tc = c;
    a = (a*a  + b*c) % mod;
    b = (ta*b + b*d) % mod;
    c = (c*ta + d*c) % mod;
    d = (tc*tb+ d*d) % mod;

    n >>= 1;  // Уменьшаем степень вдвое

  }
  return rc;
}

//возвращает n-е число Фибоначчи
int fib_n(int n)
{
	//F(n)
	int x = 1;
	//F(n-1)
	int y = 0;
	for (int i = 0; i < n; i++)
	{
		x += y;
		y = x - y;

		x %= mod;
		y %= mod;
	}
	return y;
}

int main()
{
    int n;
    cin >> n;
    cout << fib(n);


    return 0;
}
