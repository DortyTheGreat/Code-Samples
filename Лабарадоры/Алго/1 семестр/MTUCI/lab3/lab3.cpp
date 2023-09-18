
#include <iostream>
#include <cmath>

const double PI = acos(-1);
using namespace std;

void func4();
double x, y, z;


int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Ввод x= "; cin >> x;
    cout << endl << "Ввод y = "; cin >> y;
    func4(x, y, z);
    cout << endl << "результат z= " << z << endl;
    system("PAUSE");
    return 0;
}

void func4() {
    z = 1 / (2 * PI) - x * sqrt(2.5 * pow(10, 3) * y) * abs(cos(pow(x, 3)));
}
