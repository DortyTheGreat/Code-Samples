#include <iostream>
#include <cmath>

using namespace std;

double g(double arg){
    if(arg < 0.001 ){return log2(10000);}
return log2(1/arg);
}

double f(double arg){
if(arg > 0.99){return 1;}
double M = f(sqrt(arg));
return M*2;
}

double POINTS_RECEIVED(int procced, double WIN_PROC, double DRAW_PROC, double LOSE_PROC){
/// procced =
/// 0 - WIN
/// 1 - draw
/// 2 - lose
if (procced == 0){return g(WIN_PROC);}
if (procced == 2 ){return (-1) * g(LOSE_PROC); }
if (procced == 1){ return (-1) * g(WIN_PROC) + g(LOSE_PROC); }
}

int main()
{
    cout << POINTS_RECEIVED(0, 1, 0,0);

}
