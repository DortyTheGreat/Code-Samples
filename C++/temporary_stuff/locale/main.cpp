#include <Winnls.h>
#include <iostream>
#include <ostream>
#include <windows.h>
using namespace std;



bool MyFuncLocaleEx(LPWSTR pStr, DWORD dwFlags, LPARAM lparam) {

    wcout << *pStr << endl;
}

int _tmain(int argc, char* argv[])
{
    EnumSystemLocalesEx(MyFuncLocaleEx, 0, NULL, NULL);
    return 0;
}
