#include <iostream>
#include "bmp.h"
using namespace std;

int pixel_dist(const RGBAColor& a, const RGBAColor& b){
    //cout << "here3" << endl;
    //cout << RGBAColor(a).R << endl;
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


bool roll(double probablitiy){
    return probablitiy > ((double)(rnd(0,1000 * 1000 ))) / (1000 * 1000);
}

int main()
{
    BMP mm("in/source.bmp");

    BMP mm_closest("in/source.bmp");

    BMP mm_random_dither("in/source.bmp");

    /**
    ppppp
    ppppp
    ppxpp
    ppppp
    ppppp
    */
    BMP mm_random_dither_5x5("in/source.bmp");
    BMP mm_closest_dither_5x5("in/source.bmp");
    uint32_t channels = mm.get_channels();



    for (int32_t y = 0; y < mm.bmp_info_header.height; ++y) {
        for (int32_t x = 0; x < mm.bmp_info_header.width; ++x) {
            int n = channels * (y * mm.bmp_info_header.width + x);
            ///mm[n] = {255,255,255,255};
            //cout << "here" << endl;
            //cout << int(mm[n].R) << endl;
            //cout << int(new_[n].R) << endl;
            //cout << pixel_dist(new_[n], mm[n]) << endl;

            auto white_dist = pixel_dist(mm[n], {255,255,255});
            auto black_dist = pixel_dist(mm[n], {0,0,0});

            if (white_dist > black_dist){
                mm_closest[n] = {0,0,0};
            }else{
                mm_closest[n] = {255,255,255};
            }

            /// Black dist / (black dist + white dist)
            if ( roll(((double)(black_dist)) / (black_dist + white_dist))   ){
                mm_random_dither[n] = {255,255,255};
            }else{
                mm_random_dither[n] = {0,0,0};
            }

            int pixel_count = 0;
            int summ_black_dist = 0;
            int summ_white_dist = 0;

            for(int dx = -2; dx <= 2; dx++){
                for(int dy = -2; dy <= 2; dy++){
                    int n_x = x + dx;
                    int n_y = y + dy;

                    if (mm.inBounds({n_x,n_y})){

                        pixel_count++;
                        summ_black_dist += pixel_dist(mm[{n_x,n_y}], {0,0,0});
                        summ_white_dist += pixel_dist(mm[{n_x,n_y}], {255,255,255});
                    }

                }
            }

            ///cout << summ_black_dist << " " << summ_white_dist << endl;

            if (summ_white_dist > summ_black_dist){
                mm_closest_dither_5x5[n] = {0,0,0};
            }else{
                mm_closest_dither_5x5[n] = {255,255,255};
            }

            /// Black dist / (black dist + white dist)
            if ( roll(((double)(summ_black_dist)) / (summ_black_dist + summ_white_dist))   ){
                mm_random_dither_5x5[n] = {255,255,255};
            }else{
                mm_random_dither_5x5[n] = {0,0,0};
            }

            ///cout << x << " " << y << endl;



        }
    }
    mm_closest.write( "out/closest.bmp" );
    mm_random_dither.write( "out/random_dither.bmp" );
    mm_random_dither_5x5.write( "out/random5x5.bmp" );
    mm_closest_dither_5x5.write( "out/closest5x5.bmp" );
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



    cout << "Hello world!" << endl;
    return 0;
}
