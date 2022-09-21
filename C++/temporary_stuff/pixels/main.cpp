#include <windows.h>
#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.14

int main()
{
    //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    int pixel =0;

    //Choose any color
    COLORREF COLOR= RGB(255,255,255);

    //Draw pixels

    for(int time = 0;time < 1000000;time++){
        for(double i = 0; i < PI * 4; i += 0.05)
        {
            SetPixel(mydc,pixel,(int)(50+25*cos(i+time)),COLOR);
            pixel+=1;
        }
        ReleaseDC(myconsole, mydc);
    }


    cin.ignore();
    return 0;
}
