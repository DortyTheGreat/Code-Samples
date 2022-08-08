
#include <sstream>

/// https://ru.stackoverflow.com/questions/198586/%D0%9F%D1%80%D0%BE%D0%B1%D0%BB%D0%B5%D0%BC%D0%B0-%D1%81-%D0%BA%D0%BE%D0%B4%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%BE%D0%B9-%D0%BF%D1%80%D0%B8-%D1%87%D1%82%D0%B5%D0%BD%D0%B8%D0%B8-%D0%B8%D0%B7-%D1%84%D0%B0%D0%B9%D0%BB%D0%B0-%D0%B7%D0%B0%D0%BF%D0%B8%D1%81%D0%B8-%D0%B2-%D1%84%D0%B0%D0%B9%D0%BB
/// https://stackoverflow.com/questions/4775437/read-unicode-utf-8-file-into-wstring
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

wstring STW(const string s){
    wstring ret;

    for(size_t i =0;i<s.size();i++){
        ///wcout << s[i] << " ";
        ret +=  NumberToWString(s[i]);
    }
    return ret;
}

string readfile(string Lib){
    ifstream Reader(Lib.c_str());
    string Data = "";
    string Carret;

    if (Reader.fail()){
        return "[DortyException]No Such File: " +Lib + "\n";
    }

    while(!Reader.eof()){
        getline(Reader,Carret);
        Data = Data  + Carret + '\n';
    }

    Reader.close();
    return Data;
}


string get_file(string fileName){
    fstream fin(fileName.c_str());

    //fin.imbue(std::locale("zh_CN.UTF-8"));

    char c;

    string ret = "";

    while(fin.get(c)){
        cout << c;
        ret += c;
        //fout << c;
    }

    return ret;

}
