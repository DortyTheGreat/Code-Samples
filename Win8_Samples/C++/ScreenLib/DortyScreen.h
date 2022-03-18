#include <windows.h>
#include <sstream>
#include <string>       // std::string

using namespace std;

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

class Screen{
public:
    string * DATA;
    int size_;

    void init(int size__){
        size_ = size__;
        DATA = new string[size_];
    }

    void print(){
        gotoxy(0,0);
        for(int i = 0;i<size_;i++){
            cout << DATA[i] << endl;
        }
    }

};
