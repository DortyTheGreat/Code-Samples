#include <iostream>
#include <cmath>
using namespace std;
double f(double p){
    return sqrt((1-p)/p);
}
int main()
{

    int n = 100000;

    int p = 25;
    int q = 100 - p;


    double summ = 0;

    int p_occ = 0;

    for(int i =0;i<n;i++){
        int rand_ = rand() % 100;
        if (rand_ < p){
            /// p
            p_occ++;
            summ += f((double)(p)/100);
        }else{
            /// q
            summ -= f((double)(q)/100);
        }
    }


    double avg = summ / n;

    cout << p_occ << endl;

    cout << avg << endl;

    cout << "Hello world!" << endl;
    return 0;
}
