#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;



void preRun(){

    ifstream std_file_ifstream("input.txt");
    ofstream std_file_ofstream("output.txt");
    if ( std_file_ifstream.fail() == 0 ){
        cout << "INPUT_FILE_EXISTS" << endl;
        freopen("input.txt", "r", stdin);
    }else{
        cout << "INPUT FILE WAS NOT FOUND";
    }

    ///print_state(cout);
    /*
    string a;
    try{
        cin >> a;
    }
    catch( ... ){
        cout << "Oops..";
    }
    */
}

class PreLauncher{
public:

    void (*destruct_f)();

    PreLauncher(void (*func)(),void (*endel)()){
        destruct_f = endel;
        func();
    }

    ~PreLauncher()
    {
        destruct_f();
    }
};

void post_launching2(){
    cout << "after launch" << endl;
}



///PreLauncher __Dorty_Pre_Launch([]() -> void {cout << "abobus" << endl;});
PreLauncher __Dorty_Pre_Launch(preRun,post_launching2);
