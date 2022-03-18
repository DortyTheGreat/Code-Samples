//**********************************************************************
//
// Sends Win + D to toggle to the desktop
//
//**********************************************************************
#include <iostream>

#include <windows.h>
#include <winuser.h>
//#include <ostringstream>

using namespace std;

void ShowDesktop()
{
    //OutputString(L"Sending 'Win-D'\r\n");
    INPUT inputs[20] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_OEM_2;

    //Добавить до Логина



    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 0x53;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 0x43;

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = 0x52;

    inputs[4].type = INPUT_KEYBOARD;
    inputs[4].ki.wVk = 0x49;

    inputs[5].type = INPUT_KEYBOARD;
    inputs[5].ki.wVk = 0x50;

    inputs[6].type = INPUT_KEYBOARD;
    inputs[6].ki.wVk =0x54;

    inputs[7].type = INPUT_KEYBOARD;
    inputs[7].ki.wVk = VK_SPACE;

    inputs[8].type = INPUT_KEYBOARD;
    inputs[8].ki.wVk = 0x45;

    inputs[9].type = INPUT_KEYBOARD;
    inputs[9].ki.wVk = VK_RETURN;


    //Добавить до Логина



    inputs[10].type = INPUT_KEYBOARD;
    inputs[10].ki.wVk = 0x53;
    inputs[10].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[11].type = INPUT_KEYBOARD;
    inputs[11].ki.wVk = 0x43;
    inputs[12].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[13].type = INPUT_KEYBOARD;
    inputs[13].ki.wVk = 0x52;
    inputs[13].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[14].type = INPUT_KEYBOARD;
    inputs[14].ki.wVk = 0x49;
    inputs[14].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[15].type = INPUT_KEYBOARD;
    inputs[15].ki.wVk = 0x50;
    inputs[15].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[16].type = INPUT_KEYBOARD;
    inputs[16].ki.wVk =0x54;
    inputs[16].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[17].type = INPUT_KEYBOARD;
    inputs[17].ki.wVk = VK_SPACE;
    inputs[17].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[18].type = INPUT_KEYBOARD;
    inputs[18].ki.wVk = 0x45;
    inputs[18].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[19].type = INPUT_KEYBOARD;
    inputs[19].ki.wVk = VK_RETURN;
    inputs[19].ki.dwFlags = KEYEVENTF_KEYUP;


    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
       cout << "Bum, Bi" << endl;
    }
}

void ExecuteCommandE(bool Silent){
    if(Silent){
    ShellExecute(NULL, "open", "files\\Dada.exe", NULL, NULL, SW_HIDE);
    }else{
    ShellExecute(NULL, "open", "files\\Dada.exe", NULL, NULL, SW_SHOWDEFAULT);
    }

    Sleep(1000);
    //string Name = "Fruktozka - Twitch - Google Chrome";
    string Name = "WCDCBot13@play.new-places.ru - Minecraft Console Client";
    cout << Name << endl;
    HWND windowHandle = FindWindow(0, Name.c_str());
    if(windowHandle == NULL)
    {
        cout << "GOVNO" << endl;
    }
    cout << windowHandle << endl;
    cout << SetForegroundWindow(windowHandle) << endl;


    ShowDesktop();


    //system("close");
}


int main(){
ExecuteCommandE(false);

}
