#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;
HHOOK hooked = 0;

int DisplayResourceNAMessageBox()
{
    int msgboxID = MessageBox(
        NULL,
        (LPCSTR)L"Resource not available\nDo you want to try again?",
        (LPCSTR)L"Account Details",
        MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
    );

    switch (msgboxID)
    {
    case IDCANCEL:
        // TODO: add code
        break;
    case IDTRYAGAIN:
        // TODO: add code
        break;
    case IDCONTINUE:
        // TODO: add code
        break;
    }

    return msgboxID;
}

int amount = 1;

LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* ABoutKeyboard = (KBDLLHOOKSTRUCT*)lParam;
    int k_code = ABoutKeyboard->vkCode;
    int event = ABoutKeyboard->flags;


    POINT p;
    if (GetCursorPos(&p) && event == 1 && k_code >= 37 && k_code <= 40)
    {
        amount++;
        int power = sqrt(amount);

        switch(k_code){
            case 40:
                SetCursorPos(p.x,p.y+power);
                break;

            case 39:
                SetCursorPos(p.x+power,p.y);
                break;

            case 38:
                SetCursorPos(p.x,p.y-power);
                break;

            case 37:
                SetCursorPos(p.x-power,p.y);
                break;

        }

    }else{
        amount = 0;
    }

        //cursor position now in p.x and p.y

    cout << "Recieved key" << k_code <<" " <<event  << endl;

    return CallNextHookEx ( hooked, nCode , wParam, lParam );
}

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{

    //DisplayResourceNAMessageBox();


    HWND STD_HWND = GetConsoleWindow();

    ::SetWindowPos(STD_HWND, HWND_TOPMOST, 0, 0, 100, 100, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::ShowWindow(STD_HWND, SW_NORMAL);

    SetWindowPos(STD_HWND ,0,0,0 ,200,100 ,SWP_SHOWWINDOW|SWP_NOMOVE);


    SetCursorPos(0, 0);

    hooked = SetWindowsHookEx(WH_KEYBOARD_LL, &LowLevelKeyboardProc, hThisInstance, NULL);
    if (hooked == NULL)
    {
        cout << "Error" << endl;
    }

    MSG messages;

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}
