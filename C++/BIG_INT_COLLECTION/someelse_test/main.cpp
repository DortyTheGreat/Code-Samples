/// https://github.com/square1001/bigint-library/blob/master/bigint_in_one.h


#include <iostream>
#include <fstream>
#include "bigint.h"
using namespace std;

int main()
{
    ifstream fin("10k.txt");
    bigint a;
    fin >> a;

    for(int i = 0; i < 100;++i){
        a * a;
    }
    /// 1.448 100 times 10kx10k


    return 0;
}
