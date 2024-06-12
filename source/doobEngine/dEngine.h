#pragma once

#include "doobEngine/dVoice.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include "RtAudio.h"

#include <memory>


namespace doob {
	class dEngine {
	public:
		dEngine(unsigned int bufferSize, int channels, std::string name);
		~dEngine();

		bool initialize();

		void addVoice(std::unique_ptr<dVoice> voice);
		void removeVoice(size_t index);

		float generateSample();

		void setSampleRate(float sr);

		int getChannels() { return m_channels; }
		int getBufferSize() { return m_bufferSize; }
		std::string getName() { return m_name; }

		void start();
		void stop();

	private:
		static int audioCallback(void* outputBuffer, void* inputBuffer,
			unsigned int nBufferFrames, double streamTime,
			RtAudioStreamStatus status, void* userData);

		//void handleAudioCallback(float* outputBuffer, unsigned int nBufferFrames);
		
		dVector<std::unique_ptr<dVoice>> m_voices;
		RtAudio m_audio;
		unsigned int m_bufferSize;
		int m_channels;

		std::string m_name;
	};
}