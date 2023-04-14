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


#include <chrono>
#include <random>
int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);
/// [a;b]
int rnd(int a, int b) {
    return a + mt() % (b - a + 1);
}


int main()
{
    srand(time(0));


    BMP drawer("in/in1.bmp");
    uint32_t channels = drawer.get_channels();

    cout << "here" << endl;

    vector< vector< pair<int,int> > > pixel_map(drawer.bmp_info_header.height,\
                                               std::vector<pair<int,int> >(drawer.bmp_info_header.width));



    cout << "here" << endl;

    for (int32_t y = 0; y < drawer.bmp_info_header.height; ++y) {
            for (int32_t x = 0; x < drawer.bmp_info_header.width; ++x) {
                pixel_map[y][x] = {y,x};
            }
        }

    const int pixels = drawer.bmp_info_header.height * drawer.bmp_info_header.width / 3531 * 3;

    cout << "here" << endl;

    for(int pic = 1; pic <= 3531; pic += 1){

        BMP first("in/in" + to_str(pic)+ ".bmp");

        for(int pixel = 0; pixel < pixels; ++pixel){

            swap(pixel_map[rnd(0,drawer.bmp_info_header.height - 1)][rnd(0,drawer.bmp_info_header.width - 1)],\
                 pixel_map[rnd(0,drawer.bmp_info_header.height - 1)][rnd(0,drawer.bmp_info_header.width - 1)] );
        }


        for (int32_t y = 0; y < drawer.bmp_info_header.height; ++y) {
            for (int32_t x = 0; x < drawer.bmp_info_header.width; ++x) {
                int new_x = pixel_map[y][x].second;
                int new_y = pixel_map[y][x].first;
                int n = channels * (new_y * drawer.bmp_info_header.width + new_x);
                int n_normal = channels * (y * drawer.bmp_info_header.width + x);
                drawer[n_normal] = first[n];
            }
        }
        drawer.write( "out/out" + to_str(pic)+".bmp" );

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
