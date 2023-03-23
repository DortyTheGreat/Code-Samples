#include <iostream>
#include "bmp.h"

#include <ctime>

using namespace std;


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

int pixel_dist(RGBAColor a, RGBAColor b){
    //cout << "here3" << endl;
    //cout << RGBAColor(a).R << endl;
    return abs(a.R - b.R) + abs(a.G - b.G) + abs(a.B - b.B);
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
    ///uint32_t W = 100;
    ///uint32_t H = 100;

    BMP mm("in/out1.bmp");
    uint32_t channels = mm.get_channels();
    cout << "here" << endl;
    map<RGBAColor,int> mp;

    const int dist_thresh = 50;

    for(int pic = 2; pic <= 904; ++pic){

        BMP new_("in/out" + to_str(pic)+ ".bmp");

        for (int32_t y = 0; y < mm.bmp_info_header.height; ++y) {
            for (int32_t x = 0; x < mm.bmp_info_header.width; ++x) {
                int n = channels * (y * mm.bmp_info_header.width + x);
                ///mm[n] = {255,255,255,255};
                //cout << "here" << endl;
                //cout << int(mm[n].R) << endl;
                //cout << int(new_[n].R) << endl;
                //cout << pixel_dist(new_[n], mm[n]) << endl;
                if (pixel_dist(new_[n], mm[n]) > dist_thresh  ){
                    mm[n] = new_[n];
                }
                ///cout << x << " " << y << endl;

            }
        }
        mm.write( "out/out" + to_str(pic)+".bmp" );
    }

    /*
    std::vector<std::pair<int,RGBAColor> > vc;
    for(auto p : mp){
        vc.push_back({p.second,p.first});
    }
    std::sort(vc.begin(),vc.end());
    for (auto p : vc){
        cout << p.first << " " << int(p.second.R) << " " << int(p.second.G) << " " << int(p.second.B) << endl;
    }

    */








    return 0;
}
