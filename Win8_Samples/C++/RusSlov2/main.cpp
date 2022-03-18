#include <iostream>
#include <iomanip>
#include <windows.h>

#include <cstring>
#include <fstream>

using namespace std;

char str[128];
char pattern[] = "йцукен";

int main(int argc, char** argv)
{
    //setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "Привет!" << endl;
    for (int i = 32; i < 256; i++) {
        if (i % 8 == 0)
            cout << endl;
        if (i == 128)
            cout << endl;
        cout << setw(5) << i << setw(3) << (char)i;
    }
    cout << endl << "Введите строку \"йцукен\": ";
    cin >> str;
    cout << "Введено: " << str << endl;
    cout << "strings " << (strcmp(str, pattern) == 0 ? "" : "NOT ") << "identical" << endl;

    ofstream fout("cp-test.txt");
    fout << str << endl;
    fout.close();

    cin.get();
    cin.get();
    return 0;
}
