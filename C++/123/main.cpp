
#include "lib.h"
#include <iostream>

#include <sstream>
template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }




using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include "launch.h"

#include <thread>

int inc(int &a ){
    a += 1;
    return a;
}

class obj{
public:
    void do_smth(){
        cout << "Hello!";
    }
};

const std::thread::id MAIN_THREAD_ID = std::this_thread::get_id();

int main(){
    system("xdg-open ./myfile.txt >/dev/null 1>/dev/null 2>/dev/null");
    system("./binary < file.txt")
    cout << "main launched" << endl;
    clipboardxx::clipboard clipboard_;

    ///clipboard_ << "whiu324gt";
    string a;

    ///system("sleep 1s");

    clipboard_ >> a;


    if ( std::this_thread::get_id() == MAIN_THREAD_ID ){
        thread t2(main);
        t2.join();
    }else{

        stringstream ss;
        ss << "123 456";


        ///std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
        ///cin.rdbuf(ss.rdbuf());
        freopen ("myfile.txt","w",stdout);
    }




    int bbb = 10;
    ///thread t1(&inc, &bbb);

    ///obj k;

    //thread t1(&obj::do_smth, &k);
    //t1.join();



    thread t1(inc, ref(bbb));
    t1.join();

    cout << bbb << endl;





    int a2, b2;
    cin >> a2 >> b2;



    ///cin.rdbuf(cinbuf);

    cout << a2+b2 << endl;

}
