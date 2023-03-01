#include <iostream>
#include <bitset>
using namespace std;

#define int long long

/**

Идея убер простая: идти как будто решетом Эратосфена, на xor-умножением.
Ибо для xor-умножения выполняется то же главное правило для решета эратосфена

По неведомой мне причине в середине своего запуска программа тупо виснет минут на 5-7.
Что-то с памятью связано наверное, я хз что именно. Мб винда тут виновата. ХЗ
*/

int xorproduct(int x, int y) {
    int res = 0;
    for (int i = 0; i < 62; ++i) {
        if ((y >> i) & 1)
            res ^= x << i;
    }
    return res;
}

signed main()
{
    int SIEVING = 1000 * 1000 * 1000;
    bool *isPrime = new bool[SIEVING + 50];




    for(int i = 0; i < SIEVING; ++i){
        if (i % 100000 == 0){
            cout << "progress " << double(i)/SIEVING << endl;
        }
        isPrime[i] = 1;
    }

    for(int i = 2; i < SIEVING; ++i){
        if (i % 10000 == 0){
            cout << "progress " << double(i)/SIEVING << endl;
        }

        for(int j = i; j * i < SIEVING; ++j){

            isPrime[xorproduct(i,j)] = 0;
        }
    }

    cout << "done sieving" << endl;

    int index = 5 * 1000 * 1000;



    for(int i = 2; i < SIEVING; ++i){
        if (isPrime[i]){
            index--;
        }
        if (!index){
            cout << i << endl;
            break;
        }
    }


    return 0;
}
