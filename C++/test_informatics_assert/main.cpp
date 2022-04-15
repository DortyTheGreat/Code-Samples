#include <iostream>
#include <cassert>
using namespace std;


/**

При чтении из cin >> string a
a.size() == 0

И только после этого ввода будет достигнут eof



*/

int main()
{
    string a;
    cin >> a;

    if (a.size() == 0){
        assert(0);
    }

    assert(cin.eof());
    cout << "Hello world!" << endl;
    return 0;
}
