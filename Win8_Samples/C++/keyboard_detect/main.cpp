#include <iostream>
#include <windows.h>
using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    wchar_t msg[32];
    switch (uMsg)
    {
    case WM_SYSKEYDOWN:
       cout << "123" << endl;

        //OutputDebugString(msg);
        break;

    /* Handle other messages (not shown) */

    }

}

int main()
{
    cout << VK_MENU << endl;


    //SetCursorPos(100,500);


    HINSTANCE myINST;

    HWND hwnd = GetActiveWindow();



    while(1){

        if (GetKeyState(VK_MENU) & 0x8000)
        {
            cout << "ALT" << endl;
            // ALT key is down.
        }else{
        cout << "NO" << endl;
        }
        Sleep(100);

        cout << endl;


    }

    return 0;
}
