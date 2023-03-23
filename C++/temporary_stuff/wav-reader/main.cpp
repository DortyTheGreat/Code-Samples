#include <iostream>
#include "AudioFile.h"
#include <cmath>

double M_PI = acos(-1);

using namespace std;

int main()
{
    std::cout << "**********************" << std::endl;
    std::cout << "Running Example: Write Sine Wave To Audio File" << std::endl;
    std::cout << "**********************" << std::endl << std::endl;

    //---------------------------------------------------------------
    // 1. Let's setup our AudioFile instance

    AudioFile<float> a;
    a.setNumChannels (2);
    a.setNumSamplesPerChannel (44100 * 100);

    //---------------------------------------------------------------
    // 2. Create some variables to help us generate a sine wave

    const float sampleRate = 44100.f;
    const float frequencyInHz = 340.f;

    //---------------------------------------------------------------
    // 3. Write the samples to the AudioFile sample buffer

    for (int i = 0; i < a.getNumSamplesPerChannel(); i++)
    {
        for (int channel = 0; channel < a.getNumChannels(); channel++)
        {
            a.samples[channel][i] = (i*i)/(10000.0); ///sin ((static_cast<float> (i * i / 10 / 1000) / sampleRate) * frequencyInHz * 2.f * M_PI);
        }
    }

    //---------------------------------------------------------------
    // 4. Save the AudioFile

    std::string filePath = "sine-wave.wav"; // change this to somewhere useful for you
    a.save ("sine-wave.wav", AudioFileFormat::Wave);
    return 0;
}
