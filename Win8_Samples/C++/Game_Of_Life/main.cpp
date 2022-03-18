#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

int main()
{
    int MS = 30;

    int SizeX = 50;
    int SizeY = 30;

    int RandGen = 3;

    int Stability = 90;

    int GenChance = 2;
    int DeathChance = 30;

    int Data[SizeY][SizeX];
    int NewData[SizeY][SizeX];
    for(int i=0;i<SizeY;i++){
        for(int j=0;j<SizeX;j++){
            Data[i][j] = ((rand() % 100) < RandGen);
        }
    }

    for(int i=0;i<SizeY;i++){
        for(int j=0;j<SizeX;j++){
                if(Data[i][j]){cout << "#";}else{cout <<" ";}
        }
        cout << endl;
    }



    while(1){
        Sleep(MS);
        for(int i=0;i<SizeY;i++){
        for(int j=0;j<SizeX;j++){
                if(((rand() % 100) > Stability)){
                  if(Data[i][j]){
                    if (((rand() % 100) < DeathChance)){Data[i][j] = 0;}
                  }else{
                    if (((rand() % 100) < GenChance)){Data[i][j] = 1;}
                  }
                }


        }
    }

        float Cells = 0;
        gotoxy(0,0);
        for(int i=0;i<SizeY;i++){
        for(int j=0;j<SizeX;j++){
                if(Data[i][j]){cout << "#";Cells++;}else{cout <<" ";}
        }
        cout << endl;
    }
    cout << Cells/(SizeX * SizeY) * 100;

    }

}
