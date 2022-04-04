
class PreLauncher{
public:

    PreLauncher(void (*func)()){
        func();
    }
};

void pre_launching2(){
    cout << "second_start" << endl;
}



PreLauncher __Dorty_Pre_Launch([]() -> void {cout << "abobus" << endl;});

PreLauncher __Dorty_Pre_Launch2(pre_launching2);

