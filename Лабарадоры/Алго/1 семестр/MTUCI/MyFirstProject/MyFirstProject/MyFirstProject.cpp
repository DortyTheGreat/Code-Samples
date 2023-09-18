/*
// f.cpp
#include <cmath>
double f(double x, int n) {
	return pow(-1, n + 1) * pow(x, 2 * n + 1) / (4 * pow(n, 2) - 1);
}



#include <iostream>
#include <iomanip>

using namespace std;

int main ()
{
	
	double eps = 0.001, x = 0.3;
	for (int n = 1; abs(f(x, n)) > eps; ++n) {
		cout << f(x, n) << endl;
	}

	
	system("PAUSE");
	return 0;
}
*/

#include <iostream>

using namespace std;

double calc(double x, double a, double b) {
	if (x < 2) return a * sin(x) + b * cos(x);
	if (x > 3) return max(max(pow(x, 3), exp(x)),1000.0);
	return min(min(sin(x) / x, max(pow(a, x), pow(x, 3))), x * pow(log(x), 2));
}

double calc_if(double x, double a, double b) {
	double m;
	if (x < 2) return a * sin(x) + b * cos(x);
	if (x > 3) {
		if (1000.0 > exp(x)) m = 1000;
		else m = exp(x);
		if (m > pow(x, 3)) return m;
		else return pow(x, 3);
	}

	if (pow(a, x) > pow(x, 3))
		m = pow(a, x);
	else
		m = pow(x, 3);
	if (sin(x) / x < m)
		m = sin(x) / x;
	if (x * pow(log(x), 2) < m)
		m = x * pow(log(x), 2);
	return m;

}

int main() {
	double x, a, b;
	cin >> x >> a >> b;
	cout << "max-min: " << calc(x, a, b) << endl;
	cout << "if: " << calc(x, a, b) << endl;
	system("PAUSE");
	return 0;
}