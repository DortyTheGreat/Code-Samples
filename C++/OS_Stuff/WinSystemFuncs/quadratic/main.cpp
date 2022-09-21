#include <iostream>

using namespace std;
/**
C:\Windows\System32

Projects -> Build Options... -> Static linking [-static]


*/
int main(int argc, char *argv[])
{
    if (argc != 4){
        cout << "3 coefficients are required!" << endl;
        return 0;
    }
    int D = atoi(argv[2])*atoi(argv[2]) - 4*atoi(argv[1])*atoi(argv[3]);
    cout << "D = " << D;
    if (D < 0){
        cout << endl<<"D < 0, no real solutions exists" << endl;
    }
    if (D == 0){
        cout << endl;
    }
    return 0;
}
