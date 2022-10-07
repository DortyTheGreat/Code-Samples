/*
#include <iostream>
using namespace std;
void YesNo(bool a){
    if(a) cout << "true\n";
    else cout << "false\n";
}
int main()
{
    int a = 0;
    YesNo(a = 1); /// (1)
    YesNo(a = 0); /// (2)
    a = 0;
    YesNo(a == 1); /// (3)
    YesNo(a == 0); /// (4)

    ///YesNo(1 = 1); (5)

    YesNo(1 == 1); /// (6)

    YesNo('1' == '1'); /// (7)
    YesNo("1" == "1"); /// (8)
    ///YesNo("1" == '1'); (9)
    ///YesNo('1' == "1"); (10)

    YesNo(1 == 1.1); /// (11)
    YesNo(1.1 == 1); /// (12)

    YesNo( (unsigned short)(-1) == 65535 ); /// (13)
    return 0;
}

*/
#include <iostream>
#include <cmath>
double function_c(double x, double y) {
const double PI = acos(-1.0);
    return 1 / (2 * PI) - x * sqrt(2.5 * pow(10.0, 3.0) * y) * abs(cos(pow(x, 3.0)));
}

template<typename in, typename out>
in input(out to_print) {
    in x;
    std::cout << to_print;
    std::cin >> x;
    std::cout << std::endl;
    return x;
}

template<typename out1, typename out2>
void print(out1 to_print1, out2 to_print2) {
    std::cout << to_print1 << to_print2 << std::endl;
}

int main(){
    setlocale(LC_ALL, "rus");
    double x, y, c;
    int k, l, m, n;
    double const PI = acos(-1.0);
    x = input<double>("Введите x= ");
    y = input<double>("Введите y= ");
    c = function_c(x, y);
    k = c;
    l = int(c);
    m = ceil(c);
    n = floor(c);
    print("Вещественное c = ", c);
    print("Целая часть результата(неявно) k = ", k);
    print("Целая часть результата(явно) l = ", l);
    print("Округленное в большую сторону m = ", m);
    print("Округленное в меньшую сторону n = ", n);

    print("", "");

    print("Значение префиксного инкремента ++k= ", ++k);
    print("Значение постфиксного инкремента l++= ", l++);
    print("Значение k после приращения = ", k);
    print("Значение l после приращения = ", l);

    print("", "");
    system("PAUSE");
}
