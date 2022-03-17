#include <iostream>
using namespace std;

char* my_itos(int value){
    string ret = "";

    bool flag = 0;

    if (value < 0){
        flag = 1;
        value *= -1;
    }
    if (value == 0){return "0";}
    while(value != 0){
        ret = ((char)(value%10+'0')) + ret;
        value /= 10;
    }

    if (flag){
        ret = "-" + ret;
    }

    char *cstr = &ret[0];

    return cstr;
}

int main()
{


    cout << my_itos(-2281337);
    return 0;
}
