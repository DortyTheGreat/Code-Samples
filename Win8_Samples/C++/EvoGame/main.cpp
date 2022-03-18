#include <iostream>
#include <windows.h>
#include <iomanip>

const int SIZE_  = 30;

using namespace std;
void inc( int &value){
    cout << value << endl;
value++;}


void SetColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

char GetColor(int height){
int seed = (height/100) % 10;
string CHARS = " .:-=+*#%@";
return CHARS[seed];

}

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

class Point{
public:
    int height;
};


void Relax(Point &p1, Point &p2){
if(p1.height == p2.height){return;}
if(p1.height > p2.height){p1.height--;p2.height++; return;}
if(p1.height < p2.height){p1.height++;p2.height--; return;}

}

void RevRelax(Point &p1, Point &p2){
if(p1.height == p2.height){return;}
if(p1.height > p2.height){p1.height++;p2.height--; return;}
if(p1.height < p2.height){p1.height--;p2.height++; return;}

}

class ColorFulMatrix{
public:
    Point FIELD[SIZE_][SIZE_];

    void init(){
        for(int y=0;y<SIZE_;y++){
            for(int x=0;x<SIZE_;x++){
                FIELD[y][x].height = rand() % (700);
            }

        }
    }

    void print(){
        gotoxy(0,0);
        for(int y=0;y<SIZE_;y++){
            for(int x=0;x<SIZE_;x++){
                    SetColor( ( (FIELD[y][x].height/100) % 15) + 1);
                //cout << FIELD[y][x].height << " ";
                cout << "#";
                //cout << GetColor(FIELD[y][x].height);
            }
            cout << endl;
        }
    }

    void Fluctuate(int num, int PercantChance){

        for(int y=0;y<SIZE_;y++){
            for(int x=0;x<SIZE_;x++){
                    if( (rand() % 100) < PercantChance){
                 FIELD[y][x].height += (rand() % num) - (num/2);
                    }
            }

        }

    }

    void RelaxPoints(){

     for(int y=0;y<SIZE_-1;y++){
            for(int x=0;x<SIZE_-1;x++){
                    Point p0 = FIELD[y][x];

                    Point p1 = FIELD[y][x+1];
                    Point p2 = FIELD[y+1][x];
                    Point p3 = FIELD[y+1][x+1];
                    Relax(FIELD[y][x],FIELD[y][x+1]);
                    Relax(FIELD[y][x],FIELD[y+1][x]);
                    Relax(FIELD[y][x],FIELD[y+1][x+1]);
            }

        }


    }
};


int main()
{
    int num = 8;
    inc(num);
    cout << num << endl;
    ColorFulMatrix MM;
    MM.init();

    while(1){
            //cout << rand() % 100 << endl;
    Sleep(10);

    MM.RelaxPoints();
    MM.Fluctuate(300 * 2 + 1,2);
    MM.print();
    }


}
