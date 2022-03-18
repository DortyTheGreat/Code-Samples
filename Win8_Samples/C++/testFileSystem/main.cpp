#include <iostream>
#include <fstream>


using namespace std;

int main()
{
    fstream stream_;
    stream_.open ("DataBase.txt", fstream::in | fstream::out);
    stream_ << "HUI HUI";
    for(int i =0;i<1000*1000;i++){
        stream_.seekg(i*100);
        stream_.seekp(i*100);
        //stream_ << "PONYATNO";
    }

    stream_.close();

    cout << "Hello world!" << endl;
    return 0;
}
