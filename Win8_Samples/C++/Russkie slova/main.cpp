/// (Project > Build Options > Other Compile Options) compile options "-finput-charset=CP1251 -fexec-charset=CP866"


#include <iostream>

#include <stdio.h>
#include <stdlib.h> // atoi

#include <io.h>
#include <fcntl.h>
#include <conio.h>

#include <ctype.h>

#include <windows.h>

using namespace std;
class suschestvitelnoye{
public:
    wchar_t rod = 'm';/// m,z,s
};


class prilagatelnoe{
public:
    wstring root=L"говно";
prilagatelnoe(wstring root_){
root = root_;
}
private:
};
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Русский текст в консоли" << endl;

    string str = "Хуй";
    cout << str;
}
