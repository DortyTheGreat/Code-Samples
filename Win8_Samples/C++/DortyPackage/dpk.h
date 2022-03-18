#include <iostream>
#include <fstream>
using namespace std;

string BuildNum = "1";


string InitText;
string TagsText;


void GenInitText(){
    InitText = "";
    string InitText_[5];
    InitText_[0] = "Standardized Dorty Files: .dpk";
    InitText_[1] = ".dpk: " + BuildNum;
    InitText_[2] = "==";
    InitText_[3] = "==";
    InitText_[4] = "==";

    for(int i=0;i<5;i++){
        InitText += InitText_[i] + '\n';
    }

}

void GenTagsText(){
    TagsText = "";
    string TagsText_[20];
    int amountOfTags
    InitText_[0] = "Standardized Dorty Files: .dpk";
    InitText_[1] = ".dpk: " + BuildNum;
    InitText_[2] = "==";
    InitText_[3] = "==";
    InitText_[4] = "==";

    for(int i=0;i<5;i++){
        InitText += InitText_[i] + '\n';
    }

}


string HelpText = "This is .dpk file, \n -also known as DortyPackage. \n -For help ask Gosunov#0613 at Discord \n";

/// ========
/// Init Text (Build)
/// Help Text
/// Tags
/// Data
/// Logs
/// ========



///Tags:
/// Build : {Number}
/// Source : Open\Passworded
/// PasswordType : VZNER (только если Source = Passworded)
/// Date : 31.08.2021 - 19:10
/// END_TAG
///
void MakePKG(string fileName, string* DATA, int DataCount){

    GenInitText();

    string DotName = ".dpk";
    ofstream out((fileName + DotName).c_str());

    out << InitText;
    out << HelpText;

    out << "Tags Field : " << '\n';

    for(int i =0 ; i < DataCount; i++){
        out << DATA[i] << '\n';
    }

    out.close();
}
