#include <iostream>
#include <stdio.h>
#include "DortyScreen.h"

using namespace std;

int main()
{
    Screen SC;

    SC.init(10);
    for (int cou = 0;cou < 10000;cou++){
        for(int i =0;i< 10;i++){
            SC.DATA[i] = NumberToString(cou);
        }

        SC.print();
    }
    return 0;
}
