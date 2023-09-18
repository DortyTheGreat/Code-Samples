#include <iostream>

using namespace std;

int f(int zadach,int inter,int check){
    if (inter == 0){
        if (zadach != 0 ) return 3;
        return check;
    }

    if (inter == 1){
        return check;
    }

    if (inter == 4){
        if (zadach != 0 ) return 3;
        return 4;
    }

    if (inter == 6){
        return 0;
    }

    if (inter == 7){
        return 1;
    }

    return inter;
}

int main()
{
    int zadach,inter,check;
    cin >> zadach >> inter >> check;
    cout << f(zadach, inter, check);


    return 0;
}
