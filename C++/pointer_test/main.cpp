#include <iostream>

using namespace std;

int* add(int* a, int *b){
    int* res;
    *res = (*a)+(*b);
    return res;
}

int main()
{
    int a = 10;
    int b = 5;

    cout << add(a,b) << endl;

    cout << "Hello world!" << endl;
    return 0;
}
