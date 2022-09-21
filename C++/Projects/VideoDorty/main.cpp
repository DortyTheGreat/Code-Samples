#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

// Untested, but simple enough it should at least be close to reality...
void gotoxy(int x, int y) {
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

struct Video
{
    vector<vector<string>> Data; /// Data[frame][line]
    int frames, width, height, fps;
};

void make_pkg(string path, Video video){
    ofstream fout(path.c_str());
    fout << video.frames << " " << video.width << " " << video.height << " " << video.fps;
    fout << '\n';
    for (int frame = 0; frame < video.frames; ++frame) {
        for(int line = 0;line < video.height; ++line){
            //cout << frame << " " << line << " " << video.Data[frame][line] << '\n';
            fout <<video.Data[frame][line] << '\n';
        }

    }
}

long long get_time(){
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}

void pkg_play(string path){
    ifstream fin(path.c_str());
    Video video;
    fin >> video.frames >> video.width >> video.height >> video.fps;

    string templ;

    getline(fin,templ);

    unsigned long time_0 = get_time();

    for (int frame = 0; frame < video.frames; ++frame) {

        video.Data.push_back(vector<string> (0));

        for(int line = 0;line < video.height; ++line){
            ///cout <<"line : " <<line << endl;
            string abobus;
            ///getline(fin,video.Data[frame][line]);
            getline(fin,abobus);
            video.Data[frame].push_back(abobus);
            cout << abobus << '\n';
        }



        ///cout << a;
        //cout << frame;
        cout.flush();
        gotoxy(0,0);

        unsigned long cur_time=  get_time();

        unsigned long real_fps = (frame*1000)/(cur_time-time_0+1);

        if (real_fps > video.fps){
           this_thread::sleep_for(chrono::milliseconds(1000/video.fps));
        }


    }
}

bool f(int x, int y, int frame){
    return cos(x*y) > ((double)frame) / (300) - 1;
}

signed main() {
    ios_base::sync_with_stdio(0);

    Video graphic;
    graphic.height = 30;
    graphic.fps = 120;
    graphic.frames = 1000;
    graphic.width = 228;

    for(int frame =0;frame<graphic.frames;frame++){
        graphic.Data.push_back(vector<string> (0));
        for(int y = 0;y<graphic.height;y++){
            string str = "";
            for(int x = 0;x<100;x++){
                ///cout << x << endl;
                if ( f(x,y,frame) ){
                    str += "#";
                }else{
                    str += " ";
                }
            }
            graphic.Data[frame].push_back(str);
        }

    }


    make_pkg("here.txt", graphic);

    pkg_play("here.txt");

    //for(int i =0;i<1000*1000;i++){
    //    cout << i;
    //}
}
