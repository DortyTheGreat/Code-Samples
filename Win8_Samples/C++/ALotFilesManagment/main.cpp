#include <iostream>
#include <fstream>
#include <sstream>

#include <stdio.h>

#include <Windows.h>
#include <vector>


using namespace std;

vector<string> get_all_files_names_within_folder(string folder)
{
    vector<string> names;
    string search_path = folder + "/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if(hFind != INVALID_HANDLE_VALUE) {
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

int main()
{
    fstream fs;

    string str = "0";

    vector<string> MY;

    string path = "C:\\Users\\Mr.Snic\\Desktop\\Codes Sample\\C++\\DortyDB";

    cout << path << endl;

    MY = get_all_files_names_within_folder(path);

    for(int i =0;i<MY.size();i++){
        cout << MY[i] << endl;
    }


    cout << "Hello world!" << endl;
    return 0;
}
