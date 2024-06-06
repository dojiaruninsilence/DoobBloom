#include "dbpch.h"
#include "testAudio.h"

//temp
#include <cctype>
#include <cstdlib>

namespace doob {

    int test_cpp() {
        std::vector<RtAudio::Api> apis;
        RtAudio::getCompiledApi(apis);

        // ensure the known APIs return valid names
        std::cout << "API names by identifier (C++):\n";
        for (size_t i = 0; i < apis.size(); ++i) {
            const std::string name = RtAudio::getApiName(apis[i]);
            if (name.empty()) {
                std::cout << "Invalid name for API " << (int)apis[i] << "\n";
                exit(1);
            }
            const std::string displayName = RtAudio::getApiDisplayName(apis[i]);
            if (displayName.empty()) {
                std::cout << "Invalid display name for API " << (int)apis[i] << "\n";
                exit(1);
            }
            std::cout << "* " << (int)apis[i] << " '" << name << "': '" << displayName << "'\n";
        }

        // ensure unknown APIs return the empty string
        {
            const std::string name = RtAudio::getApiName((RtAudio::Api)-1);
            if (!name.empty()) {
                std::cout << "Bad string for invalid API '" << name << "'\n";
                exit(1);
            }
            const std::string displayName = RtAudio::getApiDisplayName((RtAudio::Api)-1);
            if (displayName != "Unknown") {
                std::cout << "Bad display string for invalid API '" << displayName << "'\n";
                exit(1);
            }
        }

        // try getting API identifier by name
        std::cout << "API identifiers by name (C++):\n";
        for (size_t i = 0; i < apis.size(); ++i) {
            std::string name = RtAudio::getApiName(apis[i]);
            if (RtAudio::getCompiledApiByName(name) != apis[i]) {
                std::cout << "Bad identifier for API '" << name << "'\n";
                exit(1);
            }
            std::cout << "* '" << name << "': " << (int)apis[i] << "\n";

            for (size_t j = 0; j < name.size(); ++j)
                name[j] = (j & 1) ? toupper(name[j]) : tolower(name[j]);
            RtAudio::Api api = RtAudio::getCompiledApiByName(name);
            if (api != RtAudio::UNSPECIFIED) {
                std::cout << "Identifier " << (int)api << " for invalid API '" << name << "'\n";
                exit(1);
            }
        }

        // try getting an API identifier by unknown name
        {
            RtAudio::Api api;
            api = RtAudio::getCompiledApiByName("");
            if (api != RtAudio::UNSPECIFIED) {
                std::cout << "Bad identifier for unknown API name\n";
                exit(1);
            }
        }

        return 0;
    }

    testAudio::testAudio() : m_bufferSize(512), m_sineWave(440.0f, 44100.0f) {}

    testAudio::~testAudio() {
        if (m_audio.isStreamOpen()) {
            m_audio.closeStream();
        }
    }

    bool testAudio::initialize() {

        /*if (m_audio.getDeviceCount() < 1) {
            std::cerr << "No audio devices found!" << std::endl;
            return false;
        }*/

        /*unsigned int devices = m_audio.getDeviceCount();
        RtAudio::DeviceInfo info;
        for (unsigned int i = 0; i < devices; i++) {
            info = m_audio.getDeviceInfo(i);
            std::cout << "Device " << i << ": " << info.name << std::endl;
        }*/


        test_cpp();

        m_channels = 2;

        RtAudio::StreamParameters parameters;
        parameters.deviceId = m_audio.getDefaultOutputDevice();
        parameters.nChannels = 2;
        parameters.firstChannel = 0;

        RtAudio::StreamOptions options;
        options.flags = RTAUDIO_MINIMIZE_LATENCY;

        m_audio.openStream(&parameters, nullptr, RTAUDIO_FLOAT32, 44100, &m_bufferSize, &audioCallback, this, &options);

        return true;
    }

    void testAudio::start() {
        if (!m_audio.isStreamRunning()) {
            m_audio.startStream();
            //std::cout << "Playing sound. Press Enter to quit." << std::endl;
        }
    }

    void testAudio::stop() {
        if (m_audio.isStreamRunning()) {
            m_audio.stopStream();
        }
    }

    int testAudio::audioCallback(void* outputBuffer, void* inputBuffer,
        unsigned int nBufferFrames, double streamTime,
        RtAudioStreamStatus status, void* userData) {

        float* buffer = static_cast<float*>(outputBuffer);

        testAudio* audio = static_cast<testAudio*>(userData);
        //audio->initialize();
        audio->m_channels = 2;

        for (unsigned int i = 0; i < nBufferFrames; ++i) {
            float sample = audio->m_sineWave.generateSample();
            for (unsigned int j = 0; j < audio->m_channels; ++j) {
                *buffer++ = sample; // Output the same sample to all channels
            }
        }

        return 0; // Return 0 to continue the audio stream
    }
}