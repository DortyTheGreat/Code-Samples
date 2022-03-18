#include <iostream>

using namespace std;

const int size_ = 10;

char matrix[size_][size_];

int main()
{

    for(int i =0;i<10;i++){
        for(int j =0;j<size_;j++){
            matrix[i][j] = ' ';
        }
    }

    cout << "Hello world!" << endl;
    return 0;
}
