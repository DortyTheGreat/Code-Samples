#include <iostream>
#include <windows.h>


using namespace std;

UINT const WM_HOOK = WM_APP + 1;
HWND hwndServer = NULL;
HINSTANCE instanceHandle = NULL;
HHOOK hookHandle = NULL;

static LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    cout << "HOOKED!" << endl;
  if (code < 0) {
    return CallNextHookEx(hookHandle, code, wParam, lParam);
  }

  //Report the event to the main window, but do not pass it to the hook chain
  SendMessage(hwndServer, WM_HOOK, wParam, lParam);
  return 1;
}

BOOL InstallHook(HWND hwndParent) {
  //Check if already hooked
  if (hwndServer != NULL) {
    return FALSE;
  }

  //Register keyboard Hook
  hookHandle = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, instanceHandle, 0);
  if (hookHandle == NULL) {
    return FALSE;
  }
  hwndServer = hwndParent;
  cout << "SUCCESSFULL CONNECT" << endl;
  return TRUE;
}

BOOL UninstallHook() {
  //Check if already unhooked
  if (hookHandle == NULL) {
    return TRUE;
  }

  //If unhook attempt fails, check whether it is because of invalid handle (in that case continue)
  if (!UnhookWindowsHookEx(hookHandle)) {
    DWORD error = GetLastError();
    if (error != ERROR_INVALID_HOOK_HANDLE) {
      return FALSE;
    }
  }
  hwndServer = NULL;
  hookHandle = NULL;
  return TRUE;
}


int main()
{

    HWND hwnd = GetActiveWindow();
    InstallHook(hwnd);

    Sleep(3000);

    cout << "Hello world!" << endl;
    return 0;
}
