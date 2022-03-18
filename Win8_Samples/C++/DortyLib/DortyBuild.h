#include <fstream>
#include <string>
#include <iostream>

using namespace std;

string Libs[100]; int AmountOfLibs=2;
string ChangeToLib = "iostream";


string GetLibTxt(string Lib){
    ifstream Reader(Lib.c_str());
    string Data = "";
    string Carret;
    while(!Reader.eof()){
        getline(Reader,Carret);
        Data = Data + Carret + '\n';
    }

    Reader.close();
    return Data;
}

void DeclareLibs(){
    Libs[0] = "DortyBuild.h";
    Libs[1] = "DortyMath.h";
}

string FuncName = "AppBuild";
void AppBuild(string MainProgrammFileName, string OutProgrammFileName){

DeclareLibs();

ofstream out(OutProgrammFileName.c_str());
ifstream in(MainProgrammFileName.c_str());

string DataReader;

while(!in.eof()){
    getline(in,DataReader);
    for(int i =0; i < AmountOfLibs; i++ ){
        if(DataReader.find(Libs[i]) != -1){
            if(i != 0){out << GetLibTxt(Libs[i]);}
            DataReader.replace(DataReader.find(Libs[i]), Libs[i].size(), ChangeToLib);

        }
    }

    if(DataReader.find(FuncName) != -1){

        int loc = DataReader.find(";",DataReader.find(FuncName)+1);
        int delta = loc - DataReader.find(FuncName) + 1;
        DataReader.replace(DataReader.find(FuncName), delta, " ");
    }

    out << DataReader << endl;
}

in.close();
out.close();


cout << "Build Has Been Done Successfully." << endl;
cout << "Made " << OutProgrammFileName << " file using" << endl;
cout << OutProgrammFileName << " file Build-Instructions" <<endl;
cout << "Original Programm will continue running" << endl << endl;
return;
}

void AppBuild(){
    AppBuild("main.cpp", "DortyBuild.cpp");
}
