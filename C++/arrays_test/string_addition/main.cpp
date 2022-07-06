#include <iostream>

using namespace std;

int main()
{
    string big_str = string(1000000, 'a');
    string b = "b";
    for(int i = 0; i < 1000;++i){
        ///big_str = big_str + 'b';
        big_str = (((((big_str + b) + b) + b) + b) + b) ;
    }

    /*

    one + -> 0.5 s

    */

    cout << "Hello world!" << endl;
    return 0;
}
