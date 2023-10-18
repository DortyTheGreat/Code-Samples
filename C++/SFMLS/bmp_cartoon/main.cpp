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

int64_t dist(const BMP& B1, const BMP& B2){
    int64_t ret = 0;

    uint32_t channels = B1.get_channels();
    for (int32_t y = 0; y < B1.bmp_info_header.height; ++y) {
        for (int32_t x = 0; x < B1.bmp_info_header.width; ++x) {
            int n = channels * (y * B1.bmp_info_header.width + x);
            ret += pixel_dist(B1[n],B2[n]);
        }
    }

    return ret;
}


#include <chrono>
#include <random>
int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);
/// [a;b]
int rnd(int a, int b) {
    return a + mt() % (b - a + 1);
}

template<typename T, typename V>
void clamp(V low, T& val, V high){
    if (val < low) val = low;
    if (val > high) val = high;
}

bool roll(double probablitiy){
    return probablitiy > ((double)(rnd(0,1000 * 1000 ))) / (1000 * 1000);
}

RGBAColor blend(const RGBAColor& a, const RGBAColor& b, double coef){
    return { (double(a.R)*coef + double(b.R)*(1-coef)), (double(a.G)*coef + double(b.G)*(1-coef)), (double(a.B)*coef + double(b.B)*(1-coef))};
}

int main()
{
    BMP mm("in/yo1.bmp");


    uint32_t channels = mm.get_channels();


    ///int64_t min_dist_global = 1001 * 1001 * 1001;
    ///min_dist_global *= 1001 * 1001 * 1001;


    BMP canvas("in/yo1.bmp");
    canvas.fill_region(0,0,mm.bmp_info_header.width, mm.bmp_info_header.height,0,0,0,0);

    for(int image = 1; image < 748; ++image ){

        BMP source("in/yo" + to_str(image) + ".bmp");


        /// Что-то типо метода отжига
        for(int i = 0; i < 5; ++i){
            int64_t d_before = dist(source,canvas);
            BMP changed = canvas;

            int32_t x0 = rnd(0,mm.bmp_info_header.width);
            int32_t x1 = rnd(x0,mm.bmp_info_header.width);

            int32_t y0 = rnd(0,mm.bmp_info_header.height);
            int32_t y1 = rnd(y0,mm.bmp_info_header.height);

            RGBAColor r = {rnd(0,255),rnd(0,255),rnd(0,255)};

            for (int32_t y = y0; y < y1; ++y) {
                for (int32_t x = x0; x < x1; ++x) {
                    int n = channels * (y * mm.bmp_info_header.width + x);

                    changed[n] = blend(changed[n], r, 0.5);
                }
            }
            int64_t d_after = dist(source,changed);

            cout << d_after << " " << d_before << endl;

            if (d_after < d_before){
                canvas = changed;
            }
        }
        cout << canvas.bmp_info_header.bit_count << endl;
        canvas.write("out/video/" + to_str(image) + ".bmp");




    }



    return 0;
}



