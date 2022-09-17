#include "prerunner.h"
#include <fstream>


/// Правила пользованием DortyBuild
/// 1. Многострочные комментарии запрещены в основном файле
/// 2. Библиотеки писать построчно
///


///
///Нельзя подключать глобальные библиотеки через "", если так сделаете получите
/// "////DortyBuild failed to load: iomanip"

const std::string version_code = "v 1.4";
const std::string ThisLibName = "DortyBuild.h";
const std::string INCLUDE_INSTEAD = "#include <fstream>";
const std::string INCLUDE_STRING = "#include";
const std::string PREFAB_TEXT = "/*\n---------------------\nThis File was Build Automatically by DortyBuild " + version_code + ".\nFor More Information ask:\n\
Discord: Тесла#9030 \n\
---Original---Code---\n\n";

std::string GetLibTxt(std::string Lib){
    std::ifstream Reader(Lib.c_str());
    std::string Data = "";
    std::string Carret;

    if (Reader.fail()){
        return "////DortyBuild failed to load: " +Lib + "\n";
    }

    while(!Reader.eof()){
        getline(Reader,Carret);
        Data += Carret + '\n';
    }

    Reader.close();
    return Data;
}

std::string FuncName = "AppBuild";

void RequrrentBuild(std::string MainProgrammFileName, std::string OutProgrammFileName, std::string lib, int depth){

    #ifdef _GLIBCXX_IOSTREAM
    std::cout << std::string(depth,'>') << " File: " << (lib+MainProgrammFileName) << std::endl;
    #endif // _GLIBCXX_IOSTREAM
    std::ofstream out(OutProgrammFileName.c_str(),std::ios::app);
    std::ifstream in((lib+MainProgrammFileName).c_str());

    std::string DataReader;

    //cout << GetLibTxt("iostream") << endl;

    while(!in.eof()){
        getline(in,DataReader);

        int find_pos = DataReader.find(INCLUDE_STRING);

        if(find_pos != -1){

            std::string Find_Lib = DataReader.substr(find_pos + INCLUDE_STRING.size());

            std::string LibName = "";

            int first_appo_pos = Find_Lib.find("\"");
            int last_appo_pos = Find_Lib.rfind("\"");

            if (first_appo_pos != -1 && last_appo_pos != -1){

                LibName = Find_Lib.substr(first_appo_pos+1,last_appo_pos-first_appo_pos-1);
                std::string Folder = "";
                if (LibName.rfind("/") != std::string::npos){
                    Folder = LibName.substr(0,LibName.rfind("/")) + "/";
                    ///cout << "Folder: " << Folder << endl;
                    LibName = LibName.substr(LibName.rfind("/")+1);
                }

                ///cout << "LibName: " << LibName << endl;
                //cout << "\{" <<LibName << "\}" << endl;
                if (LibName == ThisLibName){ /// ОБРАТИ ВНИМАНИЕ!
                    out << INCLUDE_INSTEAD << std::endl;
                }else{
                    RequrrentBuild(LibName,OutProgrammFileName,lib + Folder,depth+1);
                }
                continue;
                ///DataReader.replace(DataReader.find(INCLUDE_std::string) + first_appo_pos + find_pos, DataReader.size(), ChangeToLib);

            }


        }


        if(DataReader.find(FuncName) != std::string::npos){

            int loc = DataReader.find(";",DataReader.find(FuncName)+1);
            int delta = loc - DataReader.find(FuncName) + 1;
            DataReader.replace(DataReader.find(FuncName), delta, " ");
        }

        out << DataReader << std::endl;
    }

    in.close();
    out.close();
}





void AppBuild(std::string MainProgrammFileName, std::string OutProgrammFileName){
    std::ofstream out(OutProgrammFileName.c_str());
    out << PREFAB_TEXT;
    out << GetLibTxt(MainProgrammFileName);
    out << "*/\n";
    out.close();
    RequrrentBuild(MainProgrammFileName, OutProgrammFileName,"",1); /// "/LibName" ... + "//" + LibTxt
    #ifdef _GLIBCXX_IOSTREAM
    std::cout << std::endl;
    std::cout << "Build Has Been Done Successfully." << std::endl;
    std::cout << "Made " << OutProgrammFileName << " file using" << std::endl;
    std::cout << MainProgrammFileName << " file Build-Instructions" <<std::endl;
    std::cout << "Original Programm will continue running" << std::endl << std::endl;
    #endif // _GLIBCXX_IOSTREAM
    return;
}

void AppBuild(){
    AppBuild("main.cpp", "DortyBuild.cpp");
}

#ifndef NO_INSTANT_BUILD
Prerunner _INSTANT_BUILD(AppBuild);
#endif // NO_INSTANT_BUILD
