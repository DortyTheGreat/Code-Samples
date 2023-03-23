#include <iostream>
#include "AudioFile.h"
#include <cmath>

double M_PI = acos(-1);

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int main()
{
    std::cout << "**********************" << std::endl;
    std::cout << "Running Example: Write Sine Wave To Audio File" << std::endl;
    std::cout << "**********************" << std::endl << std::endl;

    //---------------------------------------------------------------
    // 1. Let's setup our AudioFile instance


    AudioFile<float> aria;

    AudioFile<float> new_aria;

    bool loadedOK = aria.load ("money.wav");

    new_aria = aria;
    float gain = 2.5f;

    float max_aria = -100000;

    int64_t Hz = 44100.0 / ( 115.0 / 60.0);



    float p = 0.1;
    float q = 0.1;

    for (int64_t i = 0; i < aria.getNumSamplesPerChannel(); i++)
    {
        int offset = 2 * (!( (i/Hz) %2)) - 1;

        int64_t real_i = i + offset*Hz;
        if (real_i < 0 || real_i >= aria.getNumSamplesPerChannel() ){
            real_i = i;
        }
        if (offset == 1){
            new_aria.samples[0][i] = aria.samples[0][real_i];
            new_aria.samples[1][i] = aria.samples[1][real_i];
        }else{
            new_aria.samples[1][i] = aria.samples[0][real_i];
            new_aria.samples[0][i] = aria.samples[1][real_i];
        }

            ///gangsta.samples[channel][i] = 2 * sgn(gangsta.samples[channel][i]) / ( 1/abs(gangsta.samples[channel][i]) + 1/abs(aria.samples[channel][i]) ) ;
            ///gangsta.samples[channel][i] = (gangsta.samples[channel][i] * max( (abs(aria.samples[channel][i]) / max_aria ), 0.2f) );

    }

    //---------------------------------------------------------------
    // 4. Write audio file to disk

    std::string outputFilePath = "quieter-audio-filer.wav"; // change this to somewhere useful for you
    new_aria.save (outputFilePath, AudioFileFormat::Wave);
    return 0;
}
