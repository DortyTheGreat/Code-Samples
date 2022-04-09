#include <fstream>
#include <string>
#include <iostream>

using namespace std;


/// Правила пользованием DortyBuild
/// 1. Многострочные комментарии запрещены в основном файле
/// 2. Библиотеки писать построчно
///


///
///Нельзя подключать глобальные библиотеки через "", если так сделаете получите
/// "////DortyBuild failed to load: iomanip"

const string version_code = "v 1.3";

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
        Data = Data  + Carret + '\n';
    }

    Reader.close();
    return Data;
}

string FuncName = "AppBuild";

void RequrrentBuild(string MainProgrammFileName, string OutProgrammFileName, string lib, int depth){

///cout <<"lib: " <<  lib << endl;
for(int i =0;i<depth;i++){
    cout << ">";
}
cout << " File: " << (lib+MainProgrammFileName) << endl;

ofstream out(OutProgrammFileName.c_str(),std::ios::app);
ifstream in((lib+MainProgrammFileName).c_str());

string DataReader;

//cout << GetLibTxt("iostream") << endl;

while(!in.eof()){
    getline(in,DataReader);

        const string INCLUDE_STRING = "#include";

        int find_pos = DataReader.find(INCLUDE_STRING);

        if(find_pos != -1){

            string Find_Lib = DataReader.substr(find_pos + INCLUDE_STRING.size());

            string LibName = "";

            int first_appo_pos = Find_Lib.find("\"");
            int last_appo_pos = Find_Lib.rfind("\"");

            if (first_appo_pos == -1 || last_appo_pos == -1){
            ///pass
            }else{

                LibName = Find_Lib.substr(first_appo_pos+1,last_appo_pos-first_appo_pos-1);
                string Folder = "";
                if (LibName.rfind("/") != string::npos){
                    Folder = LibName.substr(0,LibName.rfind("/")) + "/";
                    ///cout << "Folder: " << Folder << endl;
                    LibName = LibName.substr(LibName.rfind("/")+1);
                }

                ///cout << "LibName: " << LibName << endl;
                    //cout << "\{" <<LibName << "\}" << endl;
                    if (LibName != ThisLibName){ /// ОБРАТИ ВНИМАНИЕ!
                        RequrrentBuild(LibName,OutProgrammFileName,lib + Folder,depth+1);
                    }
                    continue;
                    ///DataReader.replace(DataReader.find(INCLUDE_STRING) + first_appo_pos + find_pos, DataReader.size(), ChangeToLib);

            }


        }


    if(DataReader.find(FuncName) != string::npos){

        int loc = DataReader.find(";",DataReader.find(FuncName)+1);
        int delta = loc - DataReader.find(FuncName) + 1;
        DataReader.replace(DataReader.find(FuncName), delta, " ");
    }

    out << DataReader << endl;
}

in.close();
out.close();
}



const string PREFAB_TEXT = "/*\n---------------------\nThis File was Build Automatically by DortyBuild " + version_code + ".\nFor More Information ask:\n\
Discord: Тесла#9030 \n\
---Original---Code---\n\n";

void AppBuild(string MainProgrammFileName, string OutProgrammFileName){





    ofstream out(OutProgrammFileName.c_str());
    out << PREFAB_TEXT;
    out << GetLibTxt(MainProgrammFileName);
    out << "*/\n";
    out.close();
    RequrrentBuild(MainProgrammFileName, OutProgrammFileName,"",1); /// "/LibName" ... + "//" + LibTxt

    cout << endl;
    cout << "Build Has Been Done Successfully." << endl;
    cout << "Made " << OutProgrammFileName << " file using" << endl;
    cout << MainProgrammFileName << " file Build-Instructions" <<endl;
    cout << "Original Programm will continue running" << endl << endl;
    return;
}

void AppBuild(){
    AppBuild("main.cpp", "DortyBuild.cpp");
}
