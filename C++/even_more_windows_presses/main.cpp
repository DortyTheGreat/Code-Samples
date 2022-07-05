#include <iostream>

#include <windows.h>

using namespace std;

int main()
{

    HWND calc = FindWindow(NULL,"123");
    cout << calc << endl;
    while(1){
        Sleep(1000);
        cout << "act" << endl;
        PostMessage(calc,WM_KEYDOWN,'4',0);
    }

    cout << "Hello world!" << endl;
    return 0;
}
