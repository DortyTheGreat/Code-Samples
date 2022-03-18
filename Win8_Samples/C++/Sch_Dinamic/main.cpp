#include <iostream>

using namespace std;

const int size_ = 500;

int Data[size_];


int modulo = 1e6;



int main()
{
    int n;
    cin >> n;

    for(int i =0;i<size_;i++){
        Data[i] = 0;
    }
    Data[0] = 1;

    for(int i =1;i<size_;i++){

        int pointer = 0;
        if (i >= 1){pointer += Data[i-1];}
        if (i >= 2){pointer += Data[i-2];}
        if (i >= 5){pointer += Data[i-5];}
        if (i >= 10){pointer += Data[i-10];}

        Data[i] = pointer;
    }

    cout << Data[n];
}
