/**\

������-������������ Dorty Build'a.

��� ������ �� ������?

*/

"\"

'asd\''
struct BuildOptions{
    /// (1): ������� ��� ��������� ������ �������.
    bool clear_all_spaces;

    /// (2): ������� ��� ��������� ������ ����.
    bool clear_all_tabs;

    /// (3): ������� ��� ��������� �������, ������� �������� �������.
    bool clear_all_empty_lines;


    /// (4): ���������� ����������� (���� �������)
    bool ignore_comments;

    /// (5): ���������� ���-�����������
    bool ignore_doc_comments;


    /// (6): ���� ����������� 2 ��� ����� �������� ������, �� ��� ����� �������� �� 1. ������������, ���� (1) �������.
    bool only_1_space;

    /// (7): �������� ����� � ������ ���������� ����� (���� ������ �� ���������, �� �������� ������)
    const char* prefab_text;
};

#include <fstream>
std::string a = "\
asd";
using namespace std;
#include <iostream>

const BuildOptions defaultBuildOptions = {0,0,0,0,0,1,"Hello, Build!\n"};

void ProcessFile(const std::string& FileName, const std::ofstream& OutFileStream, const BuildOptions& bo, const std::string& lib_path, uint16_t depth){
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

    while (!in.eof()){
        getline(in,DataReader);

        for(int i = 0;i<DataReader.size();++i){
            cout << int(DataReader[i]) << ' ';
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
