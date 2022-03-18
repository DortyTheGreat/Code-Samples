#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

void SetColor(int text, int background)
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render
    char blank = char(219);
  for(int i =0;i<1000;i++){
    for(int j =0;j<10;j++){
            SetColor(i% 16,0);
        cout << blank <<endl;
    }
  }
}
