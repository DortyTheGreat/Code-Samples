#include <fstream>
#include <string>
#include <iostream>

using namespace std;

///
///Ќельз€ подключать глобальные библиотеки через "", если так сделаете получите
/// "////DortyBuild failed to load: iomanip"
string ChangeToLib = "\<iostream\>";
string ThisLibName = "DortyBuild.h";

string GetLibTxt(string Lib){
    ifstream Reader(Lib.c_str());
    string Data = "";
    string Carret;

    if (Reader.fail()){
        return "////DortyBuild failed to load: " +Lib + "\n";
    }

    while(!Reader.eof()){
        getline(Reader,Carret);
        Data = Data + Carret + '\n';
    }

    Reader.close();
    return Data;
}

string FuncName = "AppBuild";
void AppBuild(string MainProgrammFileName, string OutProgrammFileName){

ofstream out(OutProgrammFileName.c_str());
ifstream in(MainProgrammFileName.c_str());

string DataReader;

//cout << GetLibTxt("iostream") << endl;

while(!in.eof()){
    getline(in,DataReader);

        const string INCLUDE_STRING = "#include";

        int find_pos = DataReader.find(INCLUDE_STRING);

        if(find_pos != -1){

            ///out << GetLibTxt(Libs[i]);

            //cout << DataReader << endl;

            string Find_Lib = DataReader.substr(find_pos + INCLUDE_STRING.size());

            //cout << DataReader << endl << Find_Lib << endl;

            string LibName = "";

            int first_appo_pos = Find_Lib.find("\"");
            int last_appo_pos = Find_Lib.rfind("\"");

            if (first_appo_pos == -1 || last_appo_pos == -1){
            ///pass
            }else{

                LibName = Find_Lib.substr(first_appo_pos+1,last_appo_pos-first_appo_pos-1);

                    //cout << "\{" <<LibName << "\}" << endl;
                    if (LibName != ThisLibName){
                        out << GetLibTxt(LibName);
                    }
                    DataReader.replace(INCLUDE_STRING.size() + first_appo_pos + find_pos, DataReader.size(), ChangeToLib);

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
cout << MainProgrammFileName << " file Build-Instructions" <<endl;
cout << "Original Programm will continue running" << endl << endl;
return;
}

void AppBuild(){
    AppBuild("main.cpp", "DortyBuild.cpp");
}
