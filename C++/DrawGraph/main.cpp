#include <iostream>
#include <conio.h>
#include <thread>
#include <cmath>

///
#include "../DortyLibs/BasicWindowsLib.h"

using namespace std;

///


#include "../DortyLibs/Screen.h"

const int H = 20 * 3 * 2;
const int W = 30 * 3 * 2;

Screen scr(W,H);

double function_(double x){
    return sin(x) * 20;
}

int main()
{

    scr.init();

    ///



    /// Yscale всегда 1
    double Xscale = 0.4;

    double x_off_set = -10 * Xscale;
    const int ms = 500;


    for(int itterations = 0; itterations < 10000; itterations++){

        x_off_set = -10*Xscale + (double)(itterations) /10;

        for(int y_c = 0; y_c < H;y_c++){
            for(int x_c = 0; x_c < W; x_c++){

                double x_f = x_c*Xscale + x_off_set;
                double x_s = x_f + Xscale;

                double y_f = function_(x_f) - y_c;
                double y_s = function_(x_s) - y_c;



                const double y_d = 1;
                ///cout << y_f <<  " " << y_s << endl;
                if ( ((y_f * y_s) <= 0) || ((y_f * (y_f+y_d) ) <= 0) ){
                    ///cout << "booba" << endl;
                    scr.draw({x_c,H-y_c-1},'#');
                }else{
                    scr.draw({x_c,H-y_c-1},' ');
                }
            }

        }

        this_thread::sleep_for(chrono::milliseconds(ms));

    }

    ///


    return 0;
}
