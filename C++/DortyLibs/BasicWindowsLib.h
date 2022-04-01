#pragma once

#include <windows.h>

HANDLE STD_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);


/// Source : https://stackoverflow.com/questions/2620409/getting-hwnd-of-current-process
HWND STD_HWND = GetConsoleWindow();

void gotoxy(SHORT x, SHORT y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(STD_HANDLE, pos);
}

void gotoxy(COORD pos) {
    SetConsoleCursorPosition(STD_HANDLE, pos);
}
