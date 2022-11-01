/**\

Проект-Реинкарнация Dorty Build'a.

Что теперь он сможет?

*/

struct BuildOptions{
    /// (1): Убирает все возможные лишние пробелы.
    bool clear_all_spaces;

    /// (2): Убирает все возможные лишние табы.
    bool clear_all_tabs;

    /// (3): Убирает все возможные строчки, которые являются пустыми.
    bool clear_all_empty_lines;


    /// (4): Игнорирует комментарии (лишь обычные)
    bool ignore_comments;

    /// (5): Игнорирует док-комментарии
    bool ignore_doc_comments;


    /// (6): Если встречается 2 или более пробелов подряд, то они будут заменены на 1. Игнорируется, если (1) включён.
    bool only_1_space;

    /// (7): Добавить текст в начало созданного файла (если ничего не добавлять, то оставить пустым)
    const char* prefab_text;
};

#include <fstream>
std::string a = "\
asd";

std::string b = "\" asd";
using namespace std;
#include <iostream>

int r = \
12;

const BuildOptions defaultBuildOptions = {0,0,0,0,0,1,"Hello, Build!\n"};

void ProcessFile(const std::string& FileName, std::ofstream& OutFileStream, const BuildOptions& bo, const std::string& lib_path, uint16_t depth){
    std::ifstream in((lib_path+FileName).c_str());



    std::string DataReader;
    std::string DataReader2;

    bool inside_text_definition = 0;
    bool inside_macro_definition = 0;
    bool inside_comment = 0;
    bool inside_long_comment = 0;
    bool inside_doc_comment = 0;
    bool inside_long_doc_comment = 0;
    bool inside_code = 1;


    const uint8_t INSIDE_CODE = 0;
    const uint8_t INSIDE_COMMENT = 0;

    uint8_t location = INSIDE_CODE;

    while (!in.eof()){
        getline(in,DataReader);
        while (DataReader[DataReader.size() - 1] == '\\'){
            getline(in,DataReader2);
            DataReader += '\n';
            DataReader += DataReader2;
        }
        location = INSIDE_CODE;

        for(size_t i = 0;i<DataReader.size();++i){
            switch(location){
                case INSIDE_CODE:
                    /// #, ", ',

                    switch(DataReader[i]){
                        case '#':
                            /// ...
                        break;

                        case '\'':
                            /// ...
                        break;

                        case '\"':
                            /// ...
                        break;

                        case '\\':
                            /// skip
                        break;

                        case '\/':
                            /// Комментарий? Деление?
                            if (DataReader[i+1] == '\/'){OutFileStream << "\/\/"; ++i; location = INSIDE_COMMENT}
                        break;

                        default:
                            OutFileStream << DataReader[i];

                    }

                break;


            }
            cout << int(DataReader[i]) << ' ';
            OutFileStream << endl;
        }
        cout << std::endl;
    }
}

void AppBuild(std::string MainProgrammFileName, const std::string& OutProgrammFileName, const BuildOptions& bo = defaultBuildOptions){
    std::ofstream out(OutProgrammFileName.c_str());
    out << bo.prefab_text;
    out.close();
    ProcessFile(MainProgrammFileName, out,bo,"",0); /// "/LibName" ... + "//" + LibTxt
    #ifdef _GLIBCXX_IOSTREAM
    std::cout << std::endl;
    std::cout << "Build Has Been Done Successfully." << std::endl;
    std::cout << "Made " << OutProgrammFileName << " file using" << std::endl;
    std::cout << MainProgrammFileName << " file Build-Instructions" <<std::endl;
    std::cout << "Original Programm will continue running" << std::endl << std::endl;
    #endif // _GLIBCXX_IOSTREAM
    return;
}


#include "test_include.h"

#include <iostream>

using namespace std;

int main()
{
    AppBuild("main.cpp","DortyBuild2.cpp");
    cout << "Hello world!" << endl;
    return 0;
}


#include <ios>\
