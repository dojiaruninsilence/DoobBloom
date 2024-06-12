#include "dbpch.h"

#include "dEngine.h"

namespace doob {
	dEngine::dEngine(unsigned int bufferSize, int channels, std::string name) : m_bufferSize(bufferSize), m_channels(channels), m_name(name) {}
	dEngine::~dEngine() {
		if (m_audio.isStreamOpen()) {
			m_audio.closeStream();
		}
	}

	bool dEngine::initialize() {
		RtAudio::StreamParameters params;
		params.deviceId = m_audio.getDefaultOutputDevice();
		params.nChannels = m_channels;
		params.firstChannel = 0;

		RtAudio::StreamOptions options;
		options.flags = RTAUDIO_MINIMIZE_LATENCY;

		//m_audio.openStream(&params, nullptr, RTAUDIO_FLOAT32, 44100, &m_bufferSize, &audioCallback, this, &options);
		try {
			m_audio.openStream(&params, nullptr, RTAUDIO_FLOAT32, 44100, &m_bufferSize, &audioCallback, this, &options);
		}
		catch (RtAudioErrorType& e) {
			std::cerr << "Failed to open stream: " << e << std::endl;
			return false;
		}

		return true;
	}

	void dEngine::addVoice(std::unique_ptr<dVoice> voice) {
		m_voices.push_back(std::move(voice));
	}

	void dEngine::removeVoice(size_t index) {
		if (index < m_voices.getSize()) {
			m_voices.erase(index);
		}
	}

	float dEngine::generateSample() {
		float sample = 0.0f;
		for (auto& voice : m_voices) {
			sample += voice->generateSample();
		}
		
		return sample / m_voices.getSize(); // mix samples 
	}

	void dEngine::setSampleRate(float sr) {
		for (auto& voice : m_voices) {
			voice->setSampleRate(sr);
		}
	}

	void dEngine::start() {
		if (!m_audio.isStreamRunning()) {
			try {
				m_audio.startStream();
			}
			catch (RtAudioErrorType& e) {
				std::cerr << "Failed to start stream: " << e << std::endl;
			}
		}
	}

	void dEngine::stop() {
		if (m_audio.isStreamRunning()) {
			m_audio.stopStream();
		}
	}

	int dEngine::audioCallback(void* outputBuffer, void* inputBuffer,
		unsigned int nBufferFrames, double streamTime,
		RtAudioStreamStatus status, void* userData) {

		dEngine* engine = static_cast<dEngine*>(userData);
		//engine->handleAudioCallback(static_cast<float*>(outputBuffer), nBufferFrames);

		float* buffer = static_cast<float*>(outputBuffer);

		for (unsigned int i = 0; i < nBufferFrames; ++i) {
			float sample = engine->generateSample();
			for (unsigned int j = 0; j < engine->m_channels; ++j) {
				*buffer++ = sample; // Output the same sample to all channels
			}
		}

		return 0;
	}

	//void dEngine::handleAudioCallback(float* outputBuffer, unsigned int nBufferFrames) {
	//	/*this->m_audio = m_audio;
	//	this->m_voices = m_voices;
	//	this->m_bufferSize = m_bufferSize;
	//	this->m_channels = m_channels;*/

	//	//float* buffer = static_cast<float*>(outputBuffer);

	//	for (unsigned int i = 0; nBufferFrames; ++i) {
	//		float sample = this->generateSample();
	//		for (unsigned int j = 0; j < this->m_channels; ++j) {
	//			*outputBuffer++ = sample;
	//			//std::cout << "Generated sample: " << sample << std::endl;
	//		}
	//	}
	//}
}