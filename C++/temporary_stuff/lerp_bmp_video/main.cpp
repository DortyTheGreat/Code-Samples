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
    return abs(a.R - b.R) + abs(a.G - b.G) + abs(a.B - b.B);
}

int main()
{
    srand(time(0));


    BMP drawer("in/in1.bmp");
    uint32_t channels = drawer.get_channels();
    cout << "here" << endl;
    map<RGBAColor,int> mp;

    const int jump = 2;

    for(int pic = 1; pic <= 3501 - jump; pic += jump){

        BMP first("in/in" + to_str(pic)+ ".bmp");
        BMP second("in/in" + to_str(pic + jump)+ ".bmp");

        for(int offset = 0; offset < jump; ++offset){
            for (int32_t y = 0; y < drawer.bmp_info_header.height; ++y) {
                for (int32_t x = 0; x < drawer.bmp_info_header.width; ++x) {
                    int n = channels * (y * drawer.bmp_info_header.width + x);
                    int R = first[n].R * (jump - offset) + second[n].R * offset;
                    int G = first[n].G * (jump - offset) + second[n].G * offset;
                    int B = first[n].B * (jump - offset) + second[n].B * offset;

                    R /= jump;
                    G /= jump;
                    B /= jump;
                    drawer[n] = {R,G,B};
                }
            }
            drawer.write( "out/out" + to_str(pic + offset)+".bmp" );
        }
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
