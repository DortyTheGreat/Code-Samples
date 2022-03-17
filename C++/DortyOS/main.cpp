#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <windows.h>
#include <sstream>

#include <iostream>

#include <stdio.h>
#include <stdlib.h> // atoi

#include <io.h>
#include <fcntl.h>
#include <conio.h>

using namespace std;

void gotoxy(short x, short y) {
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void ModifyScreen(int numOfString,wstring ws,int XReturnTo, int YReturnTo){
    //CONSOLE_SCREEN_BUFFER_INFO cbsi;
    //COORD OriginalCursorPosition = cbsi.dwCursorPosition;
    //wcout << OriginalCursorPosition.Y;
    SetConsoleCursorPosition( ::GetStdHandle(STD_OUTPUT_HANDLE), {0, numOfString} );
    wcout << ws;
    SetConsoleCursorPosition( ::GetStdHandle(STD_OUTPUT_HANDLE), {XReturnTo,YReturnTo} );
}


template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

template <typename T>
  std::wstring NumberToWString ( T Number )
  {
     std::wostringstream ss;
     ss << Number;
     return ss.str();
  }

  wstring StringToWString(const std::string &s)
{
    std::wstring wsTmp(s.begin(), s.end());

    return wsTmp;
}

wstring STW(const string s){
    wstring ret;

    for(size_t i =0;i<s.size();i++){
        ///wcout << s[i] << " ";
        ret +=  NumberToWString(s[i]);
    }
    return ret;
}

void getFilesList(string filePath,string extension, vector<string> & returnFileName)
{
    WIN32_FIND_DATA fileInfo;
    HANDLE hFind;
    string  fullPath = filePath + extension;
    hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
    if (hFind != INVALID_HANDLE_VALUE){

        ///wstring w_fp = STW(filePath); /// wide file path (WFP)

        ///returnFileName.push_back(filePath+fileInfo.cFileName);
        while (FindNextFile(hFind, &fileInfo) != 0){

            ///wcout << L"printer : "<< StringToWString(filePath) << fileInfo.cFileName << endl;

            returnFileName.push_back(filePath+fileInfo.cFileName);

            ///returnFileName.push_back(fileInfo.cFileName);

        }
    }
}

bool IsDirectory(string path)
{
    DWORD attrib = GetFileAttributes(path.c_str());

    if ((attrib & FILE_ATTRIBUTE_DIRECTORY) != 0)
        return true;

    return false;
}

string RandomString(){
    int rand_ = rand() % 10000;
    return NumberToString( rand_);
}

void print_file(string fileName){
    wfstream fin(fileName.c_str());


    string name = (RandomString() + ".txt");
    wcout << L"Name: " << STW(name) << endl;
    wofstream fout(name.c_str());

    wchar_t c;

    while(fin.get(c)){
        //wcout << c;
        //fout << c;
    }

}



void OperateAllHere(string folder){

    vector<string> ab;
    fstream fin;
    getFilesList(folder,"*",ab);

    for(size_t i = 0;i<ab.size();i++){
        wcout << STW(ab[i]) << endl;
        if (!IsDirectory(ab[i])){
            //print_file(ab[i]);
        }else{
            if (ab[i].back() != '.'){
                //OperateAllHere(ab[i] + '/');
            }
        }

    }
    wcout << endl;

}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

string getFullPath( string partialPath )
{
   char full[_MAX_PATH];
   if( _fullpath( full, partialPath.c_str(), _MAX_PATH ) != NULL )
      return full;
   else
      return "error";
}

class Explorer{
public:
    string folder="";
    vector<string> data;
    int Carret_pos = 0;

    void update_data(){
        Carret_pos = 0;
        data.clear();
        getFilesList(folder,"*",data);
    }

    void change_folder(string goto_){

        string pathe = "..";
        string carr = "";

        string bubliki = "";

        for(int i =0;i<goto_.size();i++){
            if (goto_[i] == '/'){

                if (pathe != ".." && carr == ".."){
                    bubliki.resize(bubliki.size() - (3 + pathe.size()));
                    if (bubliki.size() > 0){
                        bubliki.pop_back();
                    }
                }

                pathe = carr;
                carr = "";
                bubliki += goto_[i];
            }else{
                carr += goto_[i];
                bubliki += goto_[i];
            }
        }
        //wcout << STW(bubliki) << endl;
        folder = (bubliki);
        if (folder == "/"){
            folder = "";
        }
    }

    void update_Carret(int delta){
        //getFilesList(folder,"*",data);

        ModifyScreen(Carret_pos,L" ",0,data.size()+1);

        Carret_pos += delta;
        if (Carret_pos >= (int)(data.size())){
            Carret_pos %= data.size();
        }

        if (Carret_pos < 0){
            ///wcout << "ablobus";
            Carret_pos += data.size();
        }

        ModifyScreen(Carret_pos,L">",0,data.size()+1);


    }

    void get_file_preview(string path){

        wfstream fin(path.c_str());


        ///string name = (RandomString() + ".txt");
        //wcout << L"Name: " << STW(name) << endl;
        ///wofstream fout(name.c_str());

        wchar_t c;

        int lines = 0;
        int line_limit = 4;

        int symbols = 0;
        int symbol_limit = 200;
        wcout << L"#  ";
        while(fin.get(c)){
            symbols++;
            if (c == '\n'){ lines++;}
            if (symbols > symbol_limit || lines > line_limit) break;
            wcout << c;
            if (c == '\n'){wcout << L"#  ";}
            //fout << c;
        }
        wcout << endl;



    }

    void open_file(string path){
        if (hasEnding(path,".dpk")){
            wcout << "DORTY!";
        }else{
            get_file_preview(path);
            string path2 = "C:\\Users\\saha2\\Desktop\\root\\addoninfo.txt";

            ShellExecute(NULL, "open", getFullPath(path).c_str(), NULL, NULL, SW_SHOWNOACTIVATE);

            //WinExec(path2.c_str(),1);
        }
    }

    void wait_update(){
        int input = getch();
        //wcout << input << endl;
        if (input == 224){
            /// Стрелочки
            int input = getch();
            //wcout <<input;
            /// 72 -вверх, 80 - вниз
            if (input == 72){
                /// Вверх
                update_Carret(-1);
            }
            if (input == 80){
                /// Вниз
                update_Carret(1);
            }

            if (input == 77){
                /// ->
                if (IsDirectory(data[Carret_pos])){
                    change_folder( data[Carret_pos] + '/');
                    update_data();
                    render();
                }else{
                    open_file(data[Carret_pos]);
                }

            }

        }
    }


    /// Целиком и полностью перерисовывает данные на экран
    void render(){
        gotoxy(0,0);
        system("cls");
        for(size_t i = 0;i<data.size();i++){
            if (i == Carret_pos){wcout << L"> ";}else{wcout << L"  ";}
            wcout << STW(data[i]) << '\n';

            ///if (i == Carret_pos){get_file_preview(data[i]);}

            if (!IsDirectory(data[i])){
                //print_file(ab[i]);
            }else{
                if (data[i].back() != '.'){
                    //OperateAllHere(ab[i] + '/');
                }
            }

        }
        wcout << endl;
        //wcout << endl;
    }

    void loop(){
        update_data();
        render();
        while(1){
            //render();
            wait_update();
        }
    }
};

int main()
{


    // абобсу ❦❦❦❦
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);


    Explorer main_;

    main_.folder = "";
    //main_.show();

    main_.loop();


    //cout << "абоба";

    //wcout << StringToWString("1234");;

    /*
    ab.clear();

    getFilesList("bin/Debug/","*",ab);

    for(int i = 0;i<ab.size();i++){
        cout << ab[i] << endl;
    }
    cout << endl;
    */

    cout << "Hello World!";
}
