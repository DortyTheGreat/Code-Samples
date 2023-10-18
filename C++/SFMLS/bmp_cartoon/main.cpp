#include <iostream>
#include "bmp.h"
using namespace std;

#include <sstream>
template <typename T>
std::string to_str ( T any )
{
    std::ostringstream ss;
    ss << any;
    return ss.str();
}

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

    BMP out("in/source.bmp");
    BMP glad("in/source.bmp");

    /**
    ppppp
    ppppp
    ppxpp
    ppppp
    ppppp
    */

    uint32_t channels = mm.get_channels();


    int64_t min_dist_global = 1001 * 1001 * 1001;
    min_dist_global *= 1001 * 1001 * 1001;

    vector<RGBAColor> compressors_saved;
    vector<RGBAColor> compressors_next;

    for(int tries = 0; tries <= 30 + 15*7; ++tries){

        vector<RGBAColor> compressors = compressors_saved;
        if (tries < 30){
            compressors.push_back({rnd(0,255),rnd(0,255),rnd(0,255)});
            compressors.push_back({rnd(0,255),rnd(0,255),rnd(0,255)});
            compressors.push_back({rnd(0,255),rnd(0,255),rnd(0,255)});
            compressors.push_back({rnd(0,255),rnd(0,255),rnd(0,255)});
        }
        if (tries >= 30 & tries % 15 == 0){
            compressors_saved = compressors_next;
        }
        compressors.push_back({rnd(0,255),rnd(0,255),rnd(0,255)});

        int64_t total_dist = 0;
        for (int32_t y = 0; y < mm.bmp_info_header.height; ++y) {
            for (int32_t x = 0; x < mm.bmp_info_header.width; ++x) {
                int n = channels * (y * mm.bmp_info_header.width + x);

                int min_dist = 1000;

                for(const auto& color : compressors){
                    auto pd = pixel_dist(color,mm[n]);
                    if (pd < min_dist ){
                        min_dist = pd;
                        out[n] = color;
                    }
                }
                total_dist += min_dist;

            }
        }


        /// —глаживание??

        for (int32_t y = 0; y < mm.bmp_info_header.height; ++y) {
            for (int32_t x = 0; x < mm.bmp_info_header.width; ++x) {
                int n = channels * (y * mm.bmp_info_header.width + x);


                int SummR = 0, SummG = 0, SummB = 0;

                int cou = 0;
                for(int dx = -1; dx <= 1; ++dx){
                    for(int dy = -1; dy <= 1; ++dy){
                        int n_x = x + dx;
                        int n_y = y + dy;

                        int n = channels * (n_y * mm.bmp_info_header.width + n_x);

                        if (n_x >= 0 && n_x < mm.bmp_info_header.width && n_y >= 0 && n_y < mm.bmp_info_header.height ){
                            cou++;
                            SummR += out[n].R;
                            SummG += out[n].G;
                            SummB += out[n].B;
                        }
                    }
                }

                ///cout << cou << endl;
                glad[n] = {SummR/cou, SummG/cou, SummB/cou};

            }
        }

        if (total_dist < min_dist_global){
            compressors_next = compressors;
            min_dist_global = total_dist;
            out.write( "out/colors/" + to_str(tries)+  ".bmp" );
            glad.write( "out/glad/" + to_str(tries)+  ".bmp" );
        }


    }
    return 0;

}
