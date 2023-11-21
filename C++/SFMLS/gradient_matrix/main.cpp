#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream fout("out.txt");
    for(int i = 0; i < 100; ++i){
        for(int j = 0; j < 100; ++j){
            int flag = (i == 0) || (j == 0) || (i == 100-1) || (j == 100-1);
            fout << (i+j+2) + flag*((i+j)&1)*10 << " ";
        }
        fout << endl;
    }


    return 0;
}
