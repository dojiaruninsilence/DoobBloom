#pragma once

#include "doobEngine/dVoice.h"

#include "dUI/dOscilloscope/dOscilloscopeManager.h"

#include "dUtils/dUuid.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include "RtAudio.h"

#include <memory>
#include <unordered_map>


namespace doob {
	class dEngine {
	public:
		dEngine(unsigned int bufferSize, int channels, std::string name);
		~dEngine();

		bool initialize();

		void addVoice(std::unique_ptr<dVoice> voice);
		void removeVoice(const dUuid& uuid);

		dVoice* getVoiceByUuid(const dUuid& uuid) const;

		void addOscilloscope(dOscilloscope* oscilloscope);

		float generateSample();

		void setSampleRate(float sr);

		int getChannels() { return m_channels; }
		int getBufferSize() { return m_bufferSize; }
		std::string getName() { return m_name; }
		float getSample() { return m_sample; }

		void start();
		void stop();

	private:
		static int audioCallback(void* outputBuffer, void* inputBuffer,
			unsigned int nBufferFrames, double streamTime,
			RtAudioStreamStatus status, void* userData);
		
		dVector<std::unique_ptr<dVoice>> m_voices;
		std::unordered_map<dUuid, dVoice*> m_uuidToVoiceMap;

		RtAudio m_audio;
		unsigned int m_bufferSize;
		int m_channels;

		float m_sample;
		dOscilloscope* m_oscilloscope = nullptr;

		std::string m_name;
	};
}