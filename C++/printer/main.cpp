#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream fout("output.txt");

    for(int i = 5 * (-16);i<=5*16;i+= 16){
        for(int j = 5 * (-16);j<=5*16;j+= 16){
            fout << "forceload add ~" << i << " ~"<<j << endl;
            cout << "forceload add ~" << i << " ~"<<j << endl;
        }
    }

    cout << "Hello world!" << endl;
    return 0;
}
