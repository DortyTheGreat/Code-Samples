#include <iostream>
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include <conio.h>
#include <thread>
const double E = 2.7182818284;

using namespace std;

inline double fastPow(double a, double b) {
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;
  return u.d;
}

#define sigma 1

#if(sigma)
double activation_function(double x){
    /// sigmoid
    return 1/(1 + pow(E,-x));
}

double deriv_activ_func(double x){
    return x*(1-x);
}
#else

double activation_function(double x) {
    double absx = (double)fabs(x);
    double xx;
    if(absx>8.713655f) {
        if(x>0) return 1.0f;
        else return 0.0f;
    } else {
        xx = x*x;
        if(absx>4.5f) {
            if(x>0) return (double)(((3.2e-7*xx-8.544e-5)*xx+9.99869e-3)*x+0.953157);
            else return (double)(((3.2e-7*xx-8.544e-5)*xx+9.99869e-3)*x+0.046843);
        } else {
            return
            (double)((((((-5e-8*xx+3.6e-6)*xx-1.0621e-4)*xx+1.75410e-3)*xx-0.02045660)*xx+0.24990936)*x+0.499985);
        }
    }
}

double deriv_activ_func(double x){
    return x*(1-x);
}

#endif

const int H = 64; /// aka выстота aka количество входных нейронов aka количество выходных нейронов
const int W = 3; /// aka ширина aka количество СЛОЁВ скрытого слоя

double Edges[H][W][H]; /// aka Рёбра [ПОЗИЦИЯ_ПО_ВЫСОТЕ][ПОЗИЦИЯ_ПО_ШИРИНЕ][ВЕРШИНА_В_КОТОРУЮ_ПРОИСХОДИТ_ПЕРЕХОД]

double Net[H][W];

double deltas[H][W];

double ret[H];

/**

0
0
0
0
1
0
1



*/

/// Рандомно заполняет рёбра
void gen_edges(){
    for(int i = 0;i < H; ++i){
        for(int j = 0;j < W; ++j){
            for(int k = 0;k < H; ++k){
                Edges[i][j][k] = (rand() % 2000 - 1000)/100;
            }
        }
    }
}

double* get_result(int input[H]){


    for(int i = 0;i<H;++i){
        Net[i][0] = input[i];
    }

    for(int k = 1; k< W; ++k){
        for(int i = 0;i<H;++i){
            Net[i][k] = 0;
            for(int j = 0;j<H; ++j){
                Net[i][k] += Net[j][k-1]*Edges[j][k][i];
            }
            Net[i][k] = activation_function(Net[i][k]);
        }
    }



    for(int i = 0;i<H;++i){
        ret[i] = Net[i][W-1];
    }

    return ret;
}

int* truncate(double result[H]){
    int *ret = new int[H];
    for(int i = 0;i<H;i++){
        ret[i] = (result[i] > 0.7);
    }
    return ret;
}

int* to_bin(long long  number){
    int *ret = new int[H];
    for(int i = 0;i<H;i++){
        ret[H-i-1] = number%2;
        number /= 2;
    }
    return ret;
}



template <typename T>
void print(T* array_, int N){
    for(int i = 0;i<N;++i){cout << fixed<< setprecision(1) << setw(4)<<array_[i]<<" ";}
    cout << endl;
}


int itterations = 0;

void fix_mistakes(long long number){
    int *num = to_bin(number);
    double *result = get_result(num);
    int *waiting_for = to_bin(number+1);


    double avg_deltas = 0;

    double last_deltas[H];

    for (int i = 0;i<H;++i){
        deltas[i][W-1] = waiting_for[i] - result[i];
        last_deltas[i] = deltas[i][W-1];
        avg_deltas += abs(deltas[i][W-1]);
    }


    for(int k = W-2; k>-1; --k ){
        for(int i = 0; i < H; ++i){
            deltas[i][k] = 0;
        }
    }

    for(int k = W-1; k>0; --k ){
        for(int i = 0; i < H; ++i){
            for (int j = 0; j < H; ++j){
                deltas[j][k-1] += deltas[i][k] * Edges[j][k][i];
            }
        }
    }

    /// Подсчёт дельт



    const double training_constant = 0.1;

    for(int k = 1; k< W; ++k){
        for(int i = 0;i<H;++i){

            for(int j = 0;j<H; ++j){

                Edges[j][k][i] += training_constant * deltas[i][k] * deriv_activ_func(Net[i][k]) * Net[j][k-1];

                /**
                КОНСТНТА
                ДЕЛЬТА КУДА ВЕДЁТ РЕБРО
                ПРОИЗВОДНАЯ В ТОЧКЕ КУДА ВЕДЁТ РЕБРО
                ЗНАЧЕНИЕ В ТОЧКЕ ОТКУДА ВЕДЁТ РЕБРО
                */
            }

        }
    }

    /// Реструктуризация рёбер


    avg_deltas /= H;

    itterations++;
    const int ticks = 40000;
    if (itterations % ticks == 0){
        print(num,H);
        print(result,H);
        print(waiting_for,H);
        print(last_deltas,H);

        cout << "AVG DELTA: " << avg_deltas*100 <<" %" << endl;
        cout << "ITTERATION: " << itterations << endl;
    }
}

int main()
{
    gen_edges();
    int number = 5;
    const int ms = 5;

    while(1){
        number = rand() % 100000;
        fix_mistakes(number);
        ///this_thread::sleep_for(chrono::milliseconds(ms));

    }
    return 0;
}
