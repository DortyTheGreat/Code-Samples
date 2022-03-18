#include <iostream>

using namespace std;

const int num_size = 1000;

const int max_am_of_mults = 20;

const int pseudo_inf = 1000000;

int pluses[num_size][max_am_of_mults];
/// pluses[a][b] - сколько надо плюсов, чтобы составить число a, используя b умножений
/// pluses[a][0] = a-1
/// pluses[a][?+1] <= pluses[a][?] (логично, ибо имея больше умножений количество плюсов не может вырасти)
/// pluses[?+n][??] <= pluses[?][??] + n

/// pluses[n*m][K+P+1] <= pluses[n][K] * pluses[m][P]

/// pluses[2][0] = 1
/// pluses[3][0] = pluses[2][0] + 1 = 2

/// pluses[4][1] = 2
void start_dinamic(){

    for(int i =0;i<num_size;i++){
        for(int j =0;j<max_am_of_mults;j++){
            pluses[i][j] = pseudo_inf;
        }
    }

    for(int i = 1;i<num_size;i++){
        pluses[i][0] = i-1;
    }

    for(int i = 0;i<max_am_of_mults;i++){
        pluses[1][i] = 0;
    }

    for(int K=0;K<max_am_of_mults;K++){
        for(int P=K;(K+P+1)<max_am_of_mults;P++){
                /// n,m -> 2... ??
            for(int n=2;n<num_size;n++){
                for(int m=2;n*m<num_size;m++){
                    pluses[n*m][K+P+1] = min(pluses[n][K] + pluses[m][P],pluses[n*m][K+P+1]);
                }
            }

        }
    }

    for(int i =1;i<num_size-1;i++){
        for(int j =0;j<max_am_of_mults-1;j++){
            pluses[i+1][j] = min(pluses[i+1][j], pluses[i][j]+1);
        }
    }

}

int main()
{

    start_dinamic();

    for(int i =0;i<100;i++){
        cout << i << " : " << pluses[i][5] << endl;;
    }

    cout << "Hello world!" << endl;
    return 0;
}
