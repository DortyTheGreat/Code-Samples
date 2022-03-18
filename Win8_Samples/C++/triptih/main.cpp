#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    FILE *inp = fopen( "input.png" , "r" );
    FILE *out = fopen( "output.png" , "w" );
    int fileSize = 7548;
    int *fileBuf = new int[fileSize];
fread(fileBuf, fileSize, 1, inp);
fwrite( fileBuf, 1, fileSize, out );
    /*
    ifstream inp("input.png");
    ofstream out("output.png");
    string DATA[10000];
    string stroka;
    int i=0;
    while(!inp.eof()){
        getline(inp,DATA[i]);i++;
    }
    for(int j=0;j<i;j++){
        out << DATA[j] << endl;
    }
    */
}
