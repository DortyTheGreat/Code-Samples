#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;

char Input;
string screen="abc\nabc\nabc\n\n\n123";
string state = "Tutorial";
string CurrentPlanet="Terra-14DB";

const string MainMenu_SwapFile = "������@��������@���������@������@����������@�����������@�����@";
const string MainMenu_Description = "����� ���������� � Space Traveler v.0.1 BETA\n";
string Game_SwapFile = "���� ����...@";
string Game_Description = "������� �������: 100/100 \n";

const string Tutorial_SwapFile = "��@���@";
const string Tutorial_Description = "������ ������ ��������? (������� ��������� ������ ��� �������������)\n";

const string Tutorial_0_SwapFile = "��@���@";
const string Tutorial_0_Description = "�� ������� � ������ ��������? (������� ��������� ����, � ����� ������ ��� ������)\n";

const string Tutorial_1_SwapFile = "..@..@�������� ��� ���������@";
const string Tutorial_1_Description = "����������� ��������� ����, �����, ����� ������� ���������, � ����� ����������� ��� ����� �������� ��������� ������\n";

const string Tutorial_2_SwapFile = "..@..@..@";
const string Tutorial_2_Description = "������ � �������� ���� ��� ������������ ��������� �����, ��� ����� ������� ��������� �����\n";

const string Tutorial_3_SwapFile = "��@";
const string Tutorial_3_Description = "������, �� �� ��������� �� ���������� ��������, �� �� ���� ��� �� ����������� ��� ����!\n";

const string Tutorial_4_SwapFile = "��������...@";
const string Tutorial_4_Description = "�� ������ ��������� ����������� �������. ���� ������ �������� ������� � ��������� ��������� ����\n";

const string Tutorial_5_SwapFile = "(������� � ������� ����)@";
const string Tutorial_5_Description = "����� � ����, �������� ���������\n";

const string Tutorial_Special_SwapFile = "���! (������� � ������� ����)@";
const string Tutorial_Special_Description = "�� ��! �� ����� ��������! ��� ��������� ����������!\n";

const string Settings_SwapFile = "��������� 1@��������� 2@";
const string Settings_Description = "��������� � ����������...\n";
const string About_SwapFile = "�������� ����������� - �����@";
const string About_Description = "���������� ���...\n";
const string Saves_SwapFile = "����������@";
const string Saves_Description = "���������� � ����������\n";
const string Mods_SwapFile = "����@";
const string Mods_Description = "� ����������\n";
const string Exit_SwapFile = "��� ���� ����������� �����...@";
const string Exit_Description = "��� ���� ����������� �����...\n";
//

double Dec_Acc(double num){
return double((long long)(num*10)+1)/10;
}
string Myto_string(double arg){
return to_string((long long)(arg)) + "." + to_string(arg-(long long)(arg) ).substr(2,1);
}
class Point3D{
public:
    double X=0,Y=0,Z=0;
    Point3D(double _X,double _Y,double _Z){
    X=_X;Y=_Y;Z=_Z;
    }

    void randomize(int diapoz1,int diapoz2){
    cout << (((diapoz1 + rand()%(diapoz2-diapoz1))*10))/10;
    X = ((double)((diapoz1 + rand()%(diapoz2-diapoz1))))/10;
    Y = ((double)((diapoz1 + rand()%(diapoz2-diapoz1))))/10;
    Z = ((double)((diapoz1 + rand()%(diapoz2-diapoz1))))/10;

    }

    double GetDistance(Point3D arg){
    return Dec_Acc(sqrt( pow(X - arg.X,2) + pow(Y - arg.Y,2) + pow(Z - arg.Z,2) ));
    }
    string return_coords(){
    return Myto_string(X) + " " + Myto_string(Y) + " " + Myto_string(Z);
    }
};

class Planet{
public:
    Point3D Location =     Point3D(0,0,0);
    string name;

};

Point3D CurrentLocation(0,0,0);


class Selector{
    public:
string DATA[50]; int SizeOfSelector=0; int CurrentString=0;
string Description=Tutorial_Description;
void AddData(string arg){
DATA[SizeOfSelector]=arg;SizeOfSelector++;
}

void FillScreen(){
    screen="" + Description + "\n";
for(int i=0;i<SizeOfSelector;i++){
if(CurrentString == i){
screen+=">   ";
}
screen+= DATA[i] + '\n';
}

}

void constructe(string arg){
string stream_;
for(int i=0;i<arg.size();i++){
    if(arg[i] != '@'){
    stream_+=arg[i];
    }else{
    AddData(stream_);
    stream_="";
    }

} //123
FillScreen();
}


void ChangeState(string arg,string Swap_File,string _Description){
    if(arg == "Game"){
        Swap_File = "123@123@234";
        _Description = "������� �������: " + CurrentPlanet + "[ " + CurrentLocation.return_coords() + " ]\n";
    }
state = arg;
SizeOfSelector=0;
CurrentString=0;
Description = _Description;
 constructe(Swap_File);
}

void MoveCursor(){
    cout << ":  "<<(int)(Input)  << " - "<<CurrentString  << endl;
    int arg = (int)(Input);
if(arg == 80 ){
    CurrentString++;
}
if(arg == 72){
    CurrentString--;
}
if(arg == 77){
    //FORWARD
    if(state == "MainMenu"){
        if(CurrentString == 0){ChangeState("Game",Game_SwapFile,Game_Description);}
        if(CurrentString == 1){ChangeState("Tutorial",Tutorial_SwapFile,Tutorial_Description);}
        if(CurrentString == 2){ChangeState("Settings",Settings_SwapFile,Settings_Description);}
        if(CurrentString == 3){ChangeState("About",About_SwapFile,About_Description);}
        if(CurrentString == 4){ChangeState("Saves",Saves_SwapFile,Saves_Description);}
        if(CurrentString == 5){ChangeState("Mods",Mods_SwapFile,Mods_Description);}
        if(CurrentString == 6){ChangeState("Exit",Exit_SwapFile,Exit_Description);}
        return;
    }
    if(state == "Tutorial"){
        if(CurrentString == 0){ChangeState("Tutorial_1",Tutorial_1_SwapFile,Tutorial_1_Description);}
        if(CurrentString == 1){ChangeState("Tutorial_0",Tutorial_0_SwapFile,Tutorial_0_Description);}
    }
    if(state == "Tutorial_0"){
        if(CurrentString == 0){ChangeState("MainMenu",MainMenu_SwapFile,MainMenu_Description);}
        if(CurrentString == 1){ChangeState("Tutorial",Tutorial_SwapFile,Tutorial_Description);}
    }
    if(state == "Tutorial_1"){
        if(CurrentString == 2){ChangeState("Tutorial_2",Tutorial_2_SwapFile,Tutorial_2_Description);return;}
    }
   if(state == "Tutorial_3"){
        if(CurrentString == 0){ChangeState("Tutorial_4",Tutorial_4_SwapFile,Tutorial_4_Description);return;}
    }
    if(state == "Tutorial_4"){
        if(CurrentString == 0){ChangeState("Tutorial_5",Tutorial_5_SwapFile,Tutorial_5_Description);return;}
    }
    if(state == "Tutorial_5"){
        if(CurrentString == 0){ChangeState("MainMenu",MainMenu_SwapFile,MainMenu_Description);return;}
    }
    if(state == "Tutorial_Special"){
        if(CurrentString == 0){ChangeState("MainMenu",MainMenu_SwapFile,MainMenu_Description);return;}
    }

}
if(arg == 75){
    //Backwards
    if(state == "Game" || state == "Settings" || state == "About"){ChangeState("MainMenu",MainMenu_SwapFile,MainMenu_Description);}
    if(state == "Saves" || state == "Mods" || state == "Exit"){ChangeState("MainMenu",MainMenu_SwapFile,MainMenu_Description);}

     if(state == "Tutorial_2"){ChangeState("Tutorial_3",Tutorial_3_SwapFile,Tutorial_3_Description);}
     if(state == "Tutorial_5"){
        if(CurrentString == 0){ChangeState("Tutorial_Special",Tutorial_Special_SwapFile,Tutorial_Special_Description);}
    }
}

CurrentString = CurrentString%SizeOfSelector;
if(CurrentString < 0){
    CurrentString = SizeOfSelector + CurrentString ;
}
}





};
Selector select_;


void Print(){
    system("cls");
    cout << screen;
    Sleep(10);
}

void calculate(){

select_.MoveCursor();
select_.FillScreen();

}
int main()
{
    srand(time(0));
    setlocale(LC_ALL,"");
    int counter=1;
    /*select_.AddData("Num1");
    select_.AddData("Num2");
    select_.AddData("Num3");
    select_.AddData("Num4");
    select_.FillScreen();
    */
    select_.constructe(Tutorial_SwapFile);
    Planet Abba;
    while(1){

        Print();
        Point3D a(0,0,0),b(10,10,10);

     cout <<endl << "Debug: "<<(int)(Input)<<" : " <<select_.CurrentString <<" - " << state <<"  " << a.GetDistance(Abba.Location) << "  " << Abba.Location.X <<endl;
        Input = getch();
        CurrentLocation.randomize(10,100);
        Abba.Location.randomize(10,100);

        calculate();
    }
}
