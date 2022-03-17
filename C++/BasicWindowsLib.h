#include <windows.h>

HANDLE STD_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);


/// Source : https://stackoverflow.com/questions/2620409/getting-hwnd-of-current-process
HWND STD_HWND = GetConsoleWindow();

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

