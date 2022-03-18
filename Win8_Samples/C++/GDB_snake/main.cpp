#include <cmath>
#include <iostream>

#include <unistd.h>

#include <chrono>
#include <ctime>
#include <thread>

#include <iomanip>

#include <queue>

using namespace std;

const int width = 16;
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



int GetNextSeed(int seed) {
    return (seed + 1); ///% (width * width + 100);
}

class Point{
public:
    int X,Y;
    //Point(int X_,int Y_){
    //X = X_;
    //Y = Y_;
    //}
};

class RelaxRequest{
public:
    int x,y,depth;

     RelaxRequest(int y_,int x_,int depth_){
        x = x_;
        y = y_;
        depth = depth_;
    }
};

class RevRelaxRequest{
public:
    int x,y,depth,walls;

     RevRelaxRequest(int y_,int x_,int depth_,int walls_){
        x = x_;
        y = y_;
        depth = depth_;
        walls = walls_;
    }
};


class ZmeikaGame {
   public:
    int FieldData[width][width];
    Point Snake;
    Point Apple;
    Point Tail;

    int TailSeed = 1;
    int turns = 0;

    int Applefied = 1;  /// под эффектом яблока
    int CurrentSeed = 1;

    int Alive = 1;

    int Populate[width][width];

    int RevPopulate[width][width];

    void start_populate(){
        for(int i = 0;i < width;i++){
                for(int j =0;j<width;j++){
                    Populate[i][j] = 100; /// pseudo_inf
                    RevPopulate[i][j] = -1; /// smaller than even 0
                }
        }
    }

    int IisNearWallOrSnake(int y,int x){
        int flag = 0;
        if (FieldData[y+1][x] != -1){flag = 1;}
        if (FieldData[y-1][x] != -1){flag = 1;}
        if (FieldData[y][x+1] != -1){flag = 1;}
        if (FieldData[y][x-1] != -1){flag = 1;}

        return flag;
    }


    queue<RelaxRequest> Ochered;
    queue<RevRelaxRequest> RevOch;

    void ReqPopulate(int y, int x,int depth){

        //cout << y << " " << x << " : " << depth << endl;



        if (FieldData[y][x] == -2){
            /// Стенка
            return;
        }

        int const_ = -2; /// надо фиксировать

        if ((FieldData[y][x] != -1) && ( (FieldData[y][x] - TailSeed) > depth + const_ ) ) {return;}



        if (Populate[y][x] <= depth){return;}

        Populate[y][x] = depth;

        Ochered.push(RelaxRequest(y+1,x,depth+1));
        Ochered.push(RelaxRequest(y,x+1,depth+1));
        Ochered.push(RelaxRequest(y-1,x,depth+1));
        Ochered.push(RelaxRequest(y,x-1,depth+1));


        while(!Ochered.empty()){
            RelaxRequest RR = Ochered.front();
            Ochered.pop();
            ReqPopulate(RR.y,RR.x,RR.depth);
        }

    }

    void RevReqPopulate(int y, int x,int depth, int walls){
        //cout << y << " " << x << " : " << depth << endl;

        if (depth == 0){return;}

        if ((Populate[y][x]+1) != depth ){return;}

       /// depth уменьшается

        if (FieldData[y][x] == -2){
            /// Стенка
            return;
        }

        if (RevPopulate[y][x] > walls){return;}


        int NewWalls = walls + IisNearWallOrSnake(y,x);

        RevPopulate[y][x] = NewWalls;




        RevOch.push(RevRelaxRequest(y+1,x,depth-1,NewWalls));
        RevOch.push(RevRelaxRequest(y,x+1,depth-1,NewWalls));
        RevOch.push(RevRelaxRequest(y-1,x,depth-1,NewWalls));
        RevOch.push(RevRelaxRequest(y,x-1,depth-1,NewWalls));


        while(!RevOch.empty()){
            RevRelaxRequest RRR = RevOch.front();
            RevOch.pop();
            RevReqPopulate(RRR.y,RRR.x,RRR.depth,RRR.walls);
        }
    }

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

        Apple.X = Snake.X + 3;
        Apple.Y = Snake.Y- 5;
    }

    void render() {






        ///gotoxy(0,0);

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
        this_thread::sleep_for(chrono::milliseconds(msBeetweenFrames));
        system("cls");
        render();

        cout << "IsAlive: " << Alive << '\n';
        cout << "Turns: " << turns << '\n';
        cout << "Apples: " << apples << "   " << '\n';
        cout << "Rating (Lower=Better): " << (double)(turns) / (double)(apples)  << '\n';
    }

    void FullGamePlayRender(int msBeetweenFrames, int RenderEveryFrame ){
        turns = 0;

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
        start_populate();
        ReqPopulate(Snake.Y,Snake.X,0);

        RevReqPopulate(Apple.Y,Apple.X,Populate[Apple.Y][Apple.X] + 1,0); /// 3ая переменная - счётчик стенок

        cout << endl;
        bool isDebug = true;
        if ( (turns > 1) && (isDebug)){
            for(int i = 0;i < width;i++){
                    for(int j =0;j<width;j++){
                        cout << setw(4) <<Populate[i][j];
                    }
                    cout << endl;
            }

            cout << endl;

            for(int i = 0;i < width;i++){
                    for(int j =0;j<width;j++){
                        cout << setw(4) <<RevPopulate[i][j];
                    }
                    cout << endl;
            }

            cout << endl;
        }

        int maxi_ = -2;

        int dX = 0;
        int dY = 0;

        if (RevPopulate[Snake.Y+1][Snake.X] > maxi_){
            dX = 0;
            dY = 1;
            maxi_ = RevPopulate[Snake.Y+1][Snake.X];
        }

        if (RevPopulate[Snake.Y-1][Snake.X] > maxi_){
            dX = 0;
            dY = -1;
            maxi_ = RevPopulate[Snake.Y-1][Snake.X];
        }

        if (RevPopulate[Snake.Y][Snake.X+1] > maxi_){
            dX = 1;
            dY = 0;
            maxi_ = RevPopulate[Snake.Y][Snake.X+1];
        }

        if (RevPopulate[Snake.Y][Snake.X-1] > maxi_){
            dX = -1;
            dY = 0;
            maxi_ = RevPopulate[Snake.Y][Snake.X-1];
        }

        move(dX,dY);

    }
};

void SnakeRunner(){
    long long TotalTurns=0;
    long long TotalApples=0;
    for(int GAMES = 0;GAMES < 20; GAMES++){
        ZmeikaGame snake;
        snake.init();
        apples = 0;
        snake.turns = 0;
            while ((apples + 3 < (W2) * (W2)) && snake.Alive) {
            snake.turns++;
            snake.MyAi();
        }
        if(snake.Alive){
            cout << "GAME " << GAMES << ";  STATE: SUCCESS;   Turns: " << snake.turns << ";     Rating: " << (double)(snake.turns)/(double)(apples) << endl;
            TotalTurns += snake.turns;
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

    snake.FullGamePlayRender(100,1);

    return 10;
}

int main() {



    srand(time(NULL));

    OldMain();

    return 10;
}
