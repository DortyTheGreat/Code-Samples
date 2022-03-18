#include <iostream>
#include <cmath>

const double E = 2.7182818284;

using namespace std;

double activation_function(double x){
    /// sigmoid
    return 1/(1 + pow(E,-x));
}


const int H = 05; /// aka выстота aka количество входных нейронов aka количество выходных нейронов
const int W = 10; /// aka ширина aka количество СЛОЁВ скрытого слоя

double Edges[H][W][H]; /// aka Рёбра [ПОЗИЦИЯ_ПО_ВЫСОТЕ][ПОЗИЦИЯ_ПО_ШИРИНЕ][ВЕРШИНА_В_КОТОРУЮ_ПРОИСХОДИТ_ПЕРЕХОД]

/// Рандомно заполняет рёбра
void gen_edges(){
    for(int i = 0;i < H; ++i){
        for(int j = 0;j < W; ++j){
            for(int k = 0;k < H; ++k){
                Edges[i][j][k] = rand() % 2000 - 1000;
            }
        }
    }
}

double* get_result(int input[H]){
    double ret[H];
}

int* to_bin(long long  number){
    int ret[H];
    for(int i = 0;i<H;i++){
        ret[i] = number%2;
        ret /= 2;
    }
    return ret;
}

int main()
{

    int number = 123;
    print(to_bin(number),H);



    cout << "Hello world!" << endl;
    return 0;
}
