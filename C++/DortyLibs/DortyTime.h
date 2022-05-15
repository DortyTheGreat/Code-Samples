#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <chrono>

class Clock{
private:
    long long start_prog_time;
    long long last_time;



public:

    Clock(){
        start_prog_time = chrono::high_resolution_clock::now().time_since_epoch().count();
        last_time = chrono::high_resolution_clock::now().time_since_epoch().count();
    }

  void tick() {
      long long time = chrono::high_resolution_clock::now().time_since_epoch().count();
      ///cout << CLOCKS_PER_SEC << endl;
      cout << (time - start_prog_time) << " (+" <<time-last_time << ")" << endl;
      last_time = time;
    }
};
