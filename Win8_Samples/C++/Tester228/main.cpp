#include <iostream>
#include <cmath>
using namespace std;
int MyBoll(int seed){
    int n =abs(seed);
    cout <<((n* n % 2) + ((n + 1) * (n+1) % 2)) << endl;
return ((n % 2) + ((n + 1) % 2)) * n;

}
int Not(int seed){
return (seed+1)%2;
}
int main()
{
    int inp;
    cin >> inp;
    int a=inp%10;
    int b= (inp/10)%10;
    int c= (inp/100)%10;
    int d= (inp/1000)%10;
     int f1 =   Not(MyBoll(a-b));
     int f2=Not(MyBoll(b-c));
     int f3=Not(MyBoll(c-d));
     int f4=Not(MyBoll(d-a));
     int f5=Not(MyBoll(a-c));
     int f6=Not(MyBoll(b-d));

     int summ =(f1+f2+f3+f4+f5+f6);
     cout << summ << endl;
     cout << (summ%2)*Not(summ/2);
}
