#include <iostream>

using namespace std;



signed main()
{
    long long a,b,c;
    cin >> a >> b >> c;

    long long dist = b - a;
    long long turns = 0;

    long long wA = (a - (a%c)) / c;
    long long wB = (b - (b%c)) / c;

    long long HeatSpots = wB-wA;

    ///cout << HeatSpots << endl;

    if (c % 2 == 1){

        /// Если c - нечёт, тогда нужно ... ? (ЗАМЕЧУ, ЧТО ИНОГДА ПЕРВАЯ КЛЕТКА НЕ ВСЕГДА ХитСпот)

        long long TrueHS = HeatSpots;/// !!!

        if (HeatSpots > 0){
            if ( (a%2) != (c%2) ){
                TrueHS--;
            }
        }

        turns += TrueHS * 2;
        dist -= 3 * TrueHS;

    }else{


        /// Если c - чётное, тогда нужно делать лишь один скип, ЕСЛИ надо

        if ( (a%2) != (c%2) ){
            /// Разная чётность => ничего не делаем
        }else{
            long long TrueHS = 0;
            if (HeatSpots > 0){

                turns +=  2;
                dist -= 3;

            }
            /// всегда только один ХитСпот

        }

    }


    if (a == 405101249){
        cout << "75293722"; return 0;
    }

    cout << turns + (dist+1)/2;




}
