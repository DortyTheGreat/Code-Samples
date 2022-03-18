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

class Entity{
public:
    double X,Y; /// Location
    int isAlive = 1;

};

class Creature : public Entity{
public:
    string name;
    double HP;
    double MinATK;
    double MaxATK;

    double Defense;

    Creature(string name_, double HP_, double MinATK_, double MaxATK_, double DP){
        name = name_;
    HP = HP_;
    MinATK = MinATK_;
    MaxATK = MaxATK_;
    Defense = DP;
    }

    void ReceivePhysDMG(double dmg){
    double TrueDamage = max(dmg - Defense,double(1));

    HP -= TrueDamage;
    }

    void Hit(Creature &target, bool isSilent){
        double dmg = MinATK + rand() % (int(MaxATK-MinATK) + 1);

        if(!isSilent){


        cout << target.name <<" Received " << dmg << " damage" << endl;
        cout << "Now " << target.name << " at " << int(target.HP) << " HP" << endl;
         }

        target.ReceivePhysDMG(dmg);
    }

    void Fight(Creature target){

    int turn = 0;
    while(1){

    turn++;

    gotoxy(0,0);

        cout << name <<" : " << HP << " HP " << endl;
        cout << target.name << " : " << target.HP << " HP " << endl;

    Sleep(1 + 2000/(turn+2));
    if(HP <= 0){cout <<name <<" has lost"; return;}
    if(target.HP <= 0){cout <<name <<" won"; return;}

    if(turn % 2){
        /// Наш Ход
        Hit(target,0);
    }else{
    target.Hit(*this,0);
    }

    }

    }
};



int main()
{
    Creature Lesha("Alexei",100,10,20,0);
    Creature Grisha("Griiiii",100,1,1,1000000);

    Lesha.Fight(Grisha);

}
