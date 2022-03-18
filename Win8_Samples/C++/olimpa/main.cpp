#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n=11;
    int Data[10000]; int size_ = 2;
    int NewData[10000];

    Data[0] = 1;
    Data[1] = 1;

    for(int i =0;i<n;i++){
    size_ = size_ * 2 - 1;
        for(int j =0;j<size_;j++){
            if(j%2 == 0){
            NewData[j] = Data[j/2];
            }else{
            NewData[j] = Data[j/2] + Data[j/2 + 1];
            }
        }
        for(int cou =0;cou<10000;cou++){
            Data[cou] = NewData[cou];
        }
    }

    int Anses[10000];

    for(int i=0;i<10000;i++){
        Anses[i] = 0;
    }

    for(int i=0;i<size_;i++){
        Anses[Data[i]]++;
        cout << Data[i] << " ";
    }
    cout << endl;

    for(int i=0;i<15;i++){

        cout << i << " " << Anses[i] << endl;
    }

}
