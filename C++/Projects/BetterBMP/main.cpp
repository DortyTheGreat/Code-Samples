#include <iostream>
#include "bmp.h"

#include <ctime>

using namespace std;

int smarter_proc(int a,int b){
    if(a<0){return (a%b) + b;}
    return a%b;
}

#include <sstream>
template <typename T>
std::string to_str( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}

int main()
{
    srand(time(0));
    /*
    // Read an image from disk and write it back:
      BMP bmp("Shapes.bmp");
      bmp.write("Shapes_copy.bmp");

      // Create a BMP image in memory, modify it, save it on disk
      BMP bmp2(800, 600);
     bmp2.fill_region(50, 20, 100, 200, 0, 0, 255, 255);
     bmp2.write("img_test.bmp");

     // Create a 24 bits/pixel BMP image in memory, modify it, save it on disk
     BMP bmp3(209, 203, false);
     bmp3.fill_region(50, 20, 100, 100, 255, 0, 255, 255);
     bmp3.write("img_test_24bits.bmp");
    cout << "Hello world!" << endl;
    */
    uint32_t W = 100;
    uint32_t H = 100;
    BMP mm(W,H,false);
    uint32_t channels = mm.bmp_info_header.bit_count / 8;





    for (uint32_t y = 0; y < H; ++y) {
        for (uint32_t x = 0; x < W; ++x) {
            int n = channels * (y * W + x);
            mm[n] = {255,255,0,0};


        }
    }



    mm.write( ("abobus" + to_str(rand() % 10000) + ".bmp").c_str() );


    return 0;
}
