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
#include <map>
#include <algorithm>
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
    ///uint32_t W = 100;
    ///uint32_t H = 100;
    BMP mm("original.bmp");
    uint32_t channels = mm.bmp_info_header.bit_count / 8;

    map<RGBAColor,int> mp;


    for (int32_t y = 0; y < mm.bmp_info_header.height; ++y) {
        for (int32_t x = 0; x < mm.bmp_info_header.width; ++x) {
            int n = channels * (y * mm.bmp_info_header.width + x);
            ///mm[n] = {255,255,255,255};
            mm[n];
            ///cout << x << " " << y << endl;

        }
    }


    std::vector<std::pair<int,RGBAColor> > vc;
    for(auto p : mp){
        vc.push_back({p.second,p.first});
    }
    std::sort(vc.begin(),vc.end());
    for (auto p : vc){
        cout << p.first << " " << int(p.second.R) << " " << int(p.second.G) << " " << int(p.second.B) << endl;
    }







    mm.write( ("abobus" + to_str(rand() % 10000) + ".bmp").c_str() );


    return 0;
}
