#include <iostream>

using namespace std;

class DinRecursion{
public:
    long long * Data;
    int Size;

    long long pseudo_NULL = -16732;

    void init(int size_){
        Size = size_;
        Data = new long long[size_];

        for(int i =0;i<Size;i++){
            Data[i] = pseudo_NULL;
        }
    }

    void debug_print(){
        for(int i =0;i<Size;i++){
            cout << Data[i] << " ";
        }
    }

    long long ReqReturn(int arg, long long value){
        if (Data[arg] != pseudo_NULL){return Data[arg];}
        Data[arg] = value;
        return value;
    }

};

DinRecursion DR;

long long fib(int n){
    if (n < 0){return DR.ReqReturn(n,0);}
    if (n == 0){return DR.ReqReturn(n,1);}
    return DR.ReqReturn(n,fib(n - 1)) + DR.ReqReturn(n,fib(n - 2));
}

int main()
{
    DR.init(10);
    cout << fib(9) << endl;




    DR.debug_print();

    return 0;
}
