#pragma comment(linker, "/STACK:367772161")

#include <iostream>



using namespace std;
int f(int n){
if (n == 100000){return n;}
return f(n+1);
}
int main()
{
    cout << f(0) << endl;
    cout << "Hello world!" << endl;
    return 0;
}
