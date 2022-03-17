#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int k;
    fin >> k;
    while(k--){

        int a, b, c;
        fin >> a >> b >> c;

        if (c <= a) {
          fout << max(a, c - 1 + b);
        }
        else {
          fout << a + b;
        }

        fout << endl;
    }

    return 0;
}
