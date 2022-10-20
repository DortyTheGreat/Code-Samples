#include <iostream>

using namespace std;

template <typename T>
void print(T* ref, int length ){
    for(int i = 0;i < length; ++i){
        cout << ref[i] << " ";
    }
    cout << endl;
}

int count_primes(int number){
    /// Важно, чтобы количество простых чисел было таким, что max_prime^2 <= number, причём next_prime^2 > number
    /// Например {2,3,5} подходит для чисел [25;48]; {2,3,5,7,11} [121,168]

    int prime_count = 5;
    int primes[5] = {2,3,5,7,11};



    int div;

    int COMPOSITES = 0;

    int inversePrimorial = 20; /// Число, которое выше чем обратный примориал, 20 - точно оверкилл, затем следует уменьшить это число
    int index_roulette[inversePrimorial] = {0,-1,-1,-1,-1,-1,-1,-1,0,0,0};
    int precalculated[inversePrimorial] = {1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1};
    bool Running = true;

    while(Running){
        bool overfalow_flag = 0;
        ///cout << "here" << endl;
        for(index_roulette[0] = index_roulette[0+1]+1; index_roulette[0] < prime_count; ++index_roulette[0]  ){
            div = precalculated[0] * primes[index_roulette[0]];
            cout << div << endl;
            if (abs(div) > number){ overfalow_flag = 1;break; }
            COMPOSITES += number / div;
        }

        for(int indexes = 0; ; ++indexes){
            cout << "i " << indexes << endl;

            print(index_roulette,6);
            print(precalculated,6);

            index_roulette[indexes+1] += 1;
            if ( (index_roulette[0] - index_roulette[indexes+1] - overfalow_flag <= indexes) || (index_roulette[indexes+1] == (prime_count - (indexes+1)) )  ){
                /// идём выше
                if (index_roulette[indexes+1] == 1){ Running = false; break; }
                continue;
            }
            /// Обратно вниз, заполняем precalculated

            for(int rev_indexes = indexes; rev_indexes > -1; --rev_indexes){
                index_roulette[rev_indexes] = index_roulette[rev_indexes+1]+1;
                precalculated[rev_indexes] = precalculated[rev_indexes+1] * primes[index_roulette[rev_indexes+1]];
            }
            break;

        }

        ///cout << "after " << endl;

        ///print(index_roulette,6);
        ///print(precalculated,6);

    }
    return number - COMPOSITES + prime_count - 1;
}

int main()
{
    cout << count_primes(150) << endl;
    cout << "Hello world!" << endl;
    return 0;
}
