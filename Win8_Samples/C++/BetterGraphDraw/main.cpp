#include <iostream>
#include <cmath>
#include <windows.h>
#include <ctime>

using namespace std;

/*
МЕЛЬНИЦА
---
double y(double x,double arg){
return arg * x;
}

double ArgOfTime(double time){
    int num = 4;
    int SpeedOfAnim = 2;
    double ArgOfAnim = double(SpeedOfAnim) / 100;
//return  fmod(time*ArgOfAnim,num) * (int((time*ArgOfAnim)/num)%2 * 2 - 1) ;

return  fmod(time*ArgOfAnim,num) + -num * (int((time*ArgOfAnim)/num)%2) ;
}
---
*/

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

bool in_range(double arg, double range){
return abs(arg) <= range;
}

double y(double x,double arg){
return sqrt(( abs(arg*arg*arg) -x*x)) ;
}

double ArgOfTime(double time){
    int num = 7;
    int SpeedOfAnim = 2;
    double ArgOfAnim = double(SpeedOfAnim) / 100;
//return  fmod(time*ArgOfAnim,num) * (int((time*ArgOfAnim)/num)%2 * 2 - 1) ;

return  fmod(time*ArgOfAnim,num) + -num * (int((time*ArgOfAnim)/num)%2) ;
}

int Relocate(double arg, int fieldSizeY){
if(arg >= 0){return fieldSizeY + int(arg);}
return fieldSizeY + int(arg);
}

int main()
{
    int fps = 100;
    int FRAMES = 1000/fps;
    int fieldSizeX = 30;
    int fieldSizeY = 10;

    int FSY = fieldSizeY * 2 + 1;
    int FSX = fieldSizeX * 2 + 1;

    char DATA[FSY][FSX]; ///

    double arg = 0;

    double time_ =0;

while(1){
    time_ += FRAMES;
    arg = ArgOfTime(time_);
    gotoxy(0,0);
    for(int i = 0;i<FSY;i++){
        for(int j = 0;j<FSX;j++){
            DATA[i][j] = ' ';
            if(i == fieldSizeY || j == fieldSizeX){DATA[i][j] = '=';}
        }
    }

    for(double X = -fieldSizeX;X<fieldSizeX+1;X+= 0.03){
        if ( in_range(y(X,arg), fieldSizeY ) ){
                //cout << Relocate(y(X,arg),fieldSizeY) << " ";
            DATA[ Relocate(-y(X,arg),fieldSizeY) ][Relocate(X,fieldSizeX) ] = '#';
        }
    }

    for(int i = 0;i<FSY;i++){
        for(int j = 0;j<FSX;j++){
            cout << DATA[i][j];

        }
        cout << endl;
    }
Sleep(FRAMES);
}

}
