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

class Screen{
private:
    int SizeX, SizeY;
    char **Data;


public:
    string AnnounceMessage = "Warning, screen wasn't declared, to clear this message type:\
 SCREEN_NAME.AnnounceMessage = \" \";";

    void FillZero(){
    for(int i=0;i<SizeY;i++){
        for(int j =0;j<SizeX;j++){
            Data[i][j] = ' ';
        }
    }
    }

    void FillOne(){
    for(int i=0;i<SizeY;i++){
        for(int j =0;j<SizeX;j++){
            Data[i][j] = '#';
        }
    }
    }

    void FillScreenWithStr(string msg){
    int cou = -1;
    for(int i=0;i<SizeY;i++){
        for(int j =0;j<SizeX;j++){
            cou++; if(cou < msg.size()){Data[i][j] = msg[cou];}else{
            Data[i][j] = ' ';
            }
        }
    }

    }

    void RawPrint(){
    for(int i=0;i<SizeY;i++){
        for(int j =0;j<SizeX;j++){
            cout << Data[i][j];
        }
        cout << endl;
    }
    }

    void FixedPrint(){
    gotoxy(0,0);
    RawPrint();
    }

    void ChangeSize(int X, int Y){
    SizeX = X;
    SizeY = Y;

    Data = new char* [Y]; // две строки в массиве
    for (int count_ = 0; count_ < Y; count_++)
        Data[count_] = new char [X]; // и пять столбцов
//  где ptrarray  – массив указателей на выделенный участок памяти под массив вещественных чисел  типа float
    FillScreenWithStr(AnnounceMessage);

    }

    Screen(){
    ChangeSize(10,10);
    }

    Screen(int X, int Y){
    ChangeSize(X,Y);
    }

};
int main()
{
   Screen MyScreen(30,10);
   MyScreen.FillOne();
   MyScreen.RawPrint();
   MyScreen.ChangeSize(50,5);
   MyScreen.RawPrint();

}
