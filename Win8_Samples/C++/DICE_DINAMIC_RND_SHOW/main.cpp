#include <iostream>
#include <iomanip>      // std::setw
using namespace std;


int main()
{
    int size__ = 40;
    int side = 3;

    int buffspace = 5;

    float DATA[size__ + side];

    for(int i =0;i<size__ + side;i++){
        DATA[i] = 0;
    }

    DATA[side] = 1;


    for(int i = side;i<size__ + side;i++){

        for(int j =0; j <side;j++){
            DATA[i] += DATA[i - 1 - j] / side;
        }
        cout << setw(buffspace) << i - side;

    }
    cout << endl;
    for(int i = side;i<size__ + side;i++){
    cout << setw(buffspace) << fixed << setprecision(buffspace - 3) << DATA[i];
    }
}
