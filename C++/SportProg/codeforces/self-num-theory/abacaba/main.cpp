#include <iostream>

using namespace std;

int main()
{
    int a;
    cin >> a;

    string l = "a";
    char cf = 'b';
    for(int i = 0; i < a; ++i){
        l += cf + l;
        cf++;
    }

    cout << l << endl;
    return 0;
}
