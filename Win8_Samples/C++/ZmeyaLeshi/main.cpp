#include <cmath>
#include <iostream>
#include <windows.h>
#include <unistd.h>

#include <chrono>
#include <ctime>
#include <thread>

using namespace std;

const int width = 32;
const int W2 = width-2; /// width-2


const char Empty_C = ' ';
const char Body_C = '#';
const char Head_C = '@';
const char Apple_C = '*';
const char Tail_C = 'x';
const char FieldChar = '$';

const string Separator = "";
const string NewLineSeparator = "";


int apples = 0;

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

int GetNextSeed(int seed) {
    return (seed + 1) % (width * width + 100);
}

class Point{
public:
    int X,Y;
    //Point(int X_,int Y_){
    //X = X_;
    //Y = Y_;
    //}
};

class ZmeikaGame {
   public:
    int FieldData[width][width];
    Point Snake;
    Point Apple;
    Point Tail;

    int TailSeed = 1;

    int Applefied = 1;  /// под эффектом яблока
    int CurrentSeed = 1;

    int Alive = 1;

    /// AI VARS
    int SkipTiles = 20;
    int PreviousSkip = 0;
    int SkippedThisTime = 0;
    /// AI VARS

    void init() {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < width; j++) {
                if ((i == 0) || (j == 0) || (i == width - 1) || (j == width - 1)) {
                    FieldData[i][j] = -2;
                    continue;
                }                      /// -2 = wall, стена сделана из самой змейки
                FieldData[i][j] = -1;  /// empty pustoi
            }
        }

        Snake.X = width / 2;
        Snake.Y = width / 2;
        FieldData[Snake.Y + 1][Snake.X] = CurrentSeed;

        Tail.X = Snake.X;
        Tail.Y = Snake.Y + 1;

        Apple.X = Snake.X;
        Apple.Y = Snake.Y- 5;
    }

    void render() {



        ///this_thread::sleep_for(chrono::milliseconds(500));
        ///system("cls");

        gotoxy(0,0);

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < width; j++) {
                if ((i == -1) || (j == -1) || (i == width) || (j == width)) {
                    cout << FieldChar << Separator;
                    continue;
                }

                if ((i == Snake.Y) && (j == Snake.X)) {
                    cout << Head_C << Separator;
                    continue;
                }
                if ((i == Apple.Y) && (j == Apple.X)) {
                    cout << Apple_C << Separator;
                    continue;
                }
                if (i == Tail.Y && j == Tail.X) {
                    cout << Tail_C << Separator;
                    continue;
                }

                if (FieldData[i][j] != -1) {
                    cout << Body_C << Separator;
                    continue;
                }
                cout << Empty_C << Separator;
            }
            cout << NewLineSeparator << '\n';
        }
    }

    void DebugRender(int turns, int msBeetweenFrames){
        Sleep(msBeetweenFrames);
        render();

        cout << "IsAlive: " << Alive << '\n';
        cout << "Turns: " << turns << '\n';
        cout << "Apples: " << apples << "   " << '\n';
        cout << "Rating (Lower=Better): " << (double)(turns) / (double)(apples)  << '\n';
    }

    void FullGamePlayRender(int msBeetweenFrames, int RenderEveryFrame ){
        int turns = 0;

        while ((apples < (width - 2) * (width - 2) - 3) && Alive) {
            turns++;
            MyAi();
            if (turns % RenderEveryFrame == 0) {
                DebugRender(turns,msBeetweenFrames);
            }
        }

        DebugRender(turns,msBeetweenFrames);
    }

    bool isFree(int y, int x) {
        if (FieldData[y][x] == -1)
            return true;
        return false;
    }

    void GenerateNewApple() {
        int OldGen = 0;
        if (OldGen) {
            Apple.X = rand() % (width - 2) + 1;
            Apple.Y = rand() % (width - 2) + 1;
        } else {
            int freespaces = 0;
            for (int y = 1; y < width - 1; y++) {
                for (int x = 1; x < width - 1; x++) {
                    if (FieldData[y][x] == -1 && !(y == Snake.Y && x == Snake.X)) {
                        freespaces++;
                    }
                }
            }
            int number;
            if(freespaces == 0){
                Alive = 0;
                return;
            }
            number = rand() % freespaces;
            int counter = 0;
            for (int y = 1; y < width - 1; y++) {
                for (int x = 1; x < width - 1; x++) {
                    if (FieldData[y][x] == -1 && !(y == Snake.Y && x == Snake.X)) {
                        if (counter == number) {
                            Apple.X = x;
                            Apple.Y = y;
                            return;
                        }
                        counter++;
                    }
                }
            }
        }
    }

    void move(int dX, int dY) {
        if ((Snake.X + dX == Apple.X) && (Snake.Y + dY == Apple.Y)) {
            Applefied = 1;
            GenerateNewApple();
            apples++;
        }

        if (Applefied) {
            /// Хвост остаётся там же, т.е. ничего не делаем

            Applefied = 0;
        } else {
            ///Хвост передвигаем

            int SearchSeed = GetNextSeed(TailSeed);

            Point NewTail;

            NewTail.X = Tail.X; NewTail.Y = Tail.Y;

            if (FieldData[Tail.Y][Tail.X + 1] == SearchSeed) {
                NewTail.X++;
            }
            if (FieldData[Tail.Y][Tail.X - 1] == SearchSeed) {
                NewTail.X--;
            }
            if (FieldData[Tail.Y + 1][Tail.X] == SearchSeed) {
                NewTail.Y++;
            }
            if (FieldData[Tail.Y - 1][Tail.X] == SearchSeed) {
                NewTail.Y--;
            }

            FieldData[Tail.Y][Tail.X] = -1;

            Tail.X = NewTail.X;
            Tail.Y = NewTail.Y;
            TailSeed = GetNextSeed(TailSeed);
        }

        CurrentSeed = GetNextSeed(CurrentSeed);
        FieldData[Snake.Y][Snake.X] = CurrentSeed;

        Snake.X += dX;
        Snake.Y += dY;

        if (FieldData[Snake.Y][Snake.X] != -1) {
            Alive = 0;
        }
    }

    void MyAi() {
        int ExtraAddition = -100;
        int ExtraDelitel = 4;
        //int skip = 1;

        if ((Snake.X == 1) && (Snake.Y == 1)) { /// самая контактная точка

            PreviousSkip = SkippedThisTime;
            SkipTiles = W2 - 1 - PreviousSkip - (apples - PreviousSkip - W2*2)/(W2-1);SkipTiles-=2;

            SkippedThisTime = 0;

            if (apples <  (W2*2)-7 ){
                SkipTiles = W2 + 7;
            }

            move(0, 1);
            return;
        }
        if ((Snake.X == (width - 2)) && (Snake.Y == 2)) {
            move(0, -1);
            return;
        }
        bool NewReighn = (FieldData[width - 2][Snake.X+1] == -1) && (FieldData[2][Snake.X+1] == -1);
        if(apples > 450){NewReighn = 0;}
        if (NewReighn){ /// Вся механика скипов
            if ((Snake.Y == (width - 2))) { /// Скип в самой нижней строчке
                if (Snake.X < (Apple.X -  1 )){ /// Условие скипа # 1 (Яблоко справа)
                move(1, 0);SkipTiles--;SkippedThisTime++;
                return;
                }

                if ( (Snake.X > (Apple.X)) ){ /// Условие скипа # 2 (Яблоко слева)
                if(Snake.X < (width - 2)){ /// Проверка для того, чтобы змейка не врезалась в стену
                move(1, 0);SkipTiles--;SkippedThisTime++;
                return;
                }
                }

            }

            if ((Snake.Y == (2))) { /// Скип в самой(предсамой) ВЕРХНЕЙ строчке
                if (Snake.X < (Apple.X - 1 )){ /// Условие скипа # 1 (Яблоко справа)
                move(1, 0);SkipTiles--;SkippedThisTime++;
                return;
                }

                if ( (Snake.X > (Apple.X)) ){ /// Условие скипа # 2 (Яблоко слева)
                if(Snake.X < (width - 2)){ /// Проверка для того, чтобы змейка не врезалась в стену
                move(1, 0);SkipTiles--;SkippedThisTime++;
                return;
                }
                }

            }
        }

        if (Snake.Y == (1)) { /// Возврат в самой САМОЙ верхней полоске
            move(-1, 0);



            return;
        }


        if ((Snake.Y == (width - 2)) && (Snake.X % 2 == 1)) { /// В самом низу
            move(1, 0);
            return;
        }
        if ((Snake.Y == 2) && (Snake.X % 2 == 0)) {
            move(1, 0);
            return;
        }

        // Работает только для width кратного четырём



        if (Snake.X % 2 == 0) {
            move(0, -1);
            return;
        }
        if (Snake.X % 2 == 1) {
            move(0, 1);
            return;
        }
    }
};

void SnakeRunner(){
    long long TotalTurns=0;
    long long TotalApples=0;
    for(int GAMES = 0;GAMES < 20; GAMES++){
        ZmeikaGame snake;
        snake.init();
        apples = 0;
        int turns = 0;
            while ((apples + 3 < (W2) * (W2)) && snake.Alive) {
            turns++;
            snake.MyAi();
        }
        if(snake.Alive){
            cout << "GAME " << GAMES << ";  STATE: SUCCESS;   Turns: " << turns << ";     Rating: " << (double)(turns)/(double)(apples) << endl;
            TotalTurns += turns;
            TotalApples += apples;
        }else{
            cout << "GAME " << GAMES <<";   STATE: FAILURE" << endl;
        }
    }

    cout << "AVG TURNS: " << TotalTurns/20 << endl;
    cout << "AVG RATING: " << (double)(TotalTurns)/(double)(TotalApples);
}

int OldMain(){
    ZmeikaGame snake;
    snake.init();

    snake.FullGamePlayRender(10,100);

    return 10;
}

int main() {
    srand(time(NULL));

    OldMain();

    return 10;
}
