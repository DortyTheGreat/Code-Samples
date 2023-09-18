#include <iostream>
#include <fstream>

#include <iostream>
#include <iomanip>
#include <sstream>



using namespace std;

int main()
{
    ifstream fin("data.txt");
    ofstream fout("out.txt");
    string data;

    while(fin >> data){
        cout << data << endl;

        if (data.substr(0,2) == "\"#"){
            std::stringstream stream;
            stream << data.substr(4,2);
            int R;
            stream >> std::hex >> R;

            stream << data.substr(6,2);
            int G;
            stream >> std::hex >> G;

            stream << data.substr(8,2);
            int B;
            stream >> std::hex >> B;
            cout << R << G << B << endl;
            fout << "{ red: " << R << ", green: " << G << ", blue: " << B << ", alpha: 255 }," << endl;

        }
    }


    return 0;
}
