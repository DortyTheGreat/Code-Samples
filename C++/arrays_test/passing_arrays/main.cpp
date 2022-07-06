#include <iostream>
#include <fstream>
using namespace std;

void a(int arr[]){
    arr[rand() % 10000]++;
}

int main()
{
    ifstream fin("10000.txt");
    int sz;
    fin >> sz; /// 10000
    int fixed_length_array[10000];
    int variable_length_array[sz];
    int *dinaminc_array = new int[10000];


    for(int i = 0; i < 100000; ++i){
        a(dinaminc_array);
    }

    /**
    fixed - 0.03 s
    variable_length_array - 0.03 s
    dinaminc_array - 0.03 s
    */


    cout << "Hello world!" << endl;
    return 0;
}
