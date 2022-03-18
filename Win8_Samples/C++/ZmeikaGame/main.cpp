#include <iostream>
#include <cmath>
#include <windows.h>
#include <ctime>

using namespace std;

const int SIZE_ = 32;

int apples=0;

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

int GetNextSeed(int seed){
return (seed+1)%(SIZE_*SIZE_ + 100);
}

class ZmeikaGame{
public:
    int FieldData[SIZE_][SIZE_];
    int SnakeXPos,SnakeYPos;
    int AppleXPos,AppleYPos;
    int TailXPos,TailYPos;

    int TailSeed = 1;

    int Applefied = 1; /// под эффектом яблока
    int CurrentSeed = 1;

    int Alive = 1;

    void init(){
        for(int i=0;i<SIZE_;i++){
            for(int j=0;j<SIZE_;j++){
                if ((i == 0) || (j == 0) || (i == SIZE_-1) || (j == SIZE_-1)){FieldData[i][j]=-2; continue; } /// -2 = wall, стена сделана из самой змейки
                FieldData[i][j] = -1; /// empty pustoi

            }

        }

        SnakeXPos =  SIZE_/2;
        SnakeYPos =  SIZE_/2;
        FieldData[SnakeYPos+1][SnakeXPos] = CurrentSeed;

        TailXPos = SnakeXPos;
        TailYPos = SnakeYPos+1;

        AppleXPos = SnakeXPos;
        AppleYPos = SnakeYPos - 5;
    }

    void render(){

        char Empty = ' ';
        char Body =  '#';
        char Head =  '@';
        char Apple = '*';
        char Separator = ' ';
        char NewLineSeparator = '\0'; /// '\n'
        char FieldChar = '$';
        char Tail = 'x';

        gotoxy(0,0);

        for(int i=0;i<SIZE_;i++){
            for(int j=0;j<SIZE_;j++){
                if ((i == -1) || (j == -1) || (i == SIZE_) || (j == SIZE_)){cout << FieldChar << Separator; continue; }
                /// (x,y) = (j,i)
                if ((i == SnakeYPos) && (j == SnakeXPos)){cout << Head << Separator; continue;}
                if ((i == AppleYPos) && (j == AppleXPos)){cout << Apple << Separator; continue;}
                if ((i == TailYPos) && (j == TailXPos)){cout << Tail << Separator; continue;}

                if (FieldData[i][j] != -1){cout << Body << Separator; continue;}
                cout << Empty << Separator;
            }
            cout <<NewLineSeparator << endl;
        }

    }

    void GenerateNewApple(){

        int OldGen = 0;
        if(OldGen){
        AppleXPos = rand() % (SIZE_-2) + 1;
        AppleYPos = rand() % (SIZE_-2) + 1;
        }else{
            int freespaces=0;
            for(int i=1;i<SIZE_-1;i++){
                for(int j=1;j<SIZE_-1;j++){
                    if ( (FieldData[i][j] == -1) && ( (i != SnakeYPos) && (j != SnakeXPos) )  ){freespaces++;}
                }
            }
            int number = rand() % freespaces;
            int counter = 0;
            for(int i=1;i<SIZE_-1;i++){
                for(int j=1;j<SIZE_-1;j++){
                    if ( (FieldData[i][j] == -1) && ( (i != SnakeYPos) && (j != SnakeXPos) )  ){

                        if(counter == number){
                            AppleXPos = j;
                            AppleYPos = i;
                            return;
                        }
                        counter++;
                    }
                }
            }
        }
    }

    void move_(int dX, int dY){

    if( ((SnakeXPos+dX) == AppleXPos) && ((SnakeYPos+dY) == AppleYPos)){Applefied = 1;GenerateNewApple();apples++;}

    if (Applefied){
    /// Хвост остаётся там же, т.е. ничего не делаем

    Applefied = 0;
    }else{
    ///Хвост передвигаем

    int SearchSeed = GetNextSeed(TailSeed);

    int NewTailXPos=TailXPos,NewTailYPos=TailYPos;

    if (FieldData[TailYPos][TailXPos+1] == SearchSeed){NewTailXPos++;}
    if (FieldData[TailYPos][TailXPos-1] == SearchSeed){NewTailXPos--;}
    if (FieldData[TailYPos+1][TailXPos] == SearchSeed){NewTailYPos++;}
    if (FieldData[TailYPos-1][TailXPos] == SearchSeed){NewTailYPos--;}

    FieldData[TailYPos][TailXPos] = -1;

    TailXPos = NewTailXPos;
    TailYPos = NewTailYPos;
    TailSeed = GetNextSeed(TailSeed);
    }

    CurrentSeed = GetNextSeed(CurrentSeed);
    FieldData[SnakeYPos][SnakeXPos] = CurrentSeed;

    SnakeXPos += dX;
    SnakeYPos += dY;


    if(FieldData[SnakeYPos][SnakeXPos] != -1){Alive = 0;}

    }

    void aiMove(){
    /// Полная хуйня, а не искусственный интелект
    if(SnakeYPos != AppleYPos){
        int direction;
        if(AppleYPos > SnakeYPos){direction = 1;}else{
            direction = -1;
        }
        move_(0,direction);
    }else{

    int direction;
    if(AppleXPos > SnakeXPos){direction = 1;}else{
        direction = -1;
    }
    move_(direction,0);
    }
    }

    void HameltonAi(){
    if((SnakeXPos == 1) && (SnakeYPos == 1)){move_(0,1);return;}
    if((SnakeXPos == (SIZE_-2) ) && (SnakeYPos == 2)){move_(0,-1);return;}

    if( (SnakeYPos == (SIZE_-2)) && (SnakeXPos%2 == 1) ){move_(1,0); return;}
    if( (SnakeYPos == 2) && (SnakeXPos%2 == 0 )){move_(1,0); return;}

    ///Работает только для SIZE_ кратного четырём

    if(SnakeYPos == (1) ){ move_(-1,0);return;}

    if(SnakeXPos%2 == 0 ){move_(0,-1);return;}
    if(SnakeXPos%2 == 1 ){move_(0,1);return;}
    }
};
int main()
{
    srand (time(NULL));

    ZmeikaGame snake;
    snake.init();
    snake.render();

    int turns=0;
    int RenderEveryFrame = 900 + 1;

    while(apples < ((SIZE_-2)*(SIZE_-2) - 30) ){
    turns++;
    ///Sleep(30);

    //snake.move_( 0 , 1);
    snake.HameltonAi();
    if(turns % RenderEveryFrame == 0){
    snake.render();
    cout << snake.Alive << endl << snake.TailXPos << " " << snake.TailYPos << "      " << endl;
    cout << "Turns: " <<turns << endl;
    cout << "Apples: " <<apples << endl;
    cout << "Rating(Lower=Better): " <<(double)(turns)/(double)(apples) << endl;
    }
    }
    ///snake.render();
    ///cout << endl << "Rating(Lower=Better): " <<(double)(turns)/(double)(apples) << endl;
    ///string pohui;
    ///cout << "HAHA! END END END!!!";
    ///cin >> pohui;
    return 0;

}
