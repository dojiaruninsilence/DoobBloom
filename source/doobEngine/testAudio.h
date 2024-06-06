#pragma once

#include <iostream>
#include "RtAudio.h" // Include the RtAudio header
#include "dNoiseGens/testSineGen.h"

namespace doob {
    class testAudio {
    public:
        testAudio();
        ~testAudio();

        bool initialize();
        void start();
        void stop();

    private:
        static int audioCallback(void* outputBuffer, void* inputBuffer,
            unsigned int nBufferFrames, double streamTime,
            RtAudioStreamStatus status, void* userData);

        RtAudio m_audio;
        unsigned int m_bufferSize;
        int m_channels; // Number of audio channels
        testSineGen m_sineWave;
    };
}