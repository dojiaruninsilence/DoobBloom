#include "dbpch.h"

#include "dEngine.h"

#include <algorithm>

namespace doob {
	dEngine::dEngine(unsigned int bufferSize, int channels, std::string name) 
		: m_bufferSize(bufferSize), m_channels(channels), m_name(name) {}

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
		dUuid voiceId = voice->getId();
		m_uuidToVoiceMap[voiceId] = voice.get();
		m_voices.push_back(std::move(voice));
	}

	void dEngine::removeVoice(const dUuid& uuid) {
		auto it = m_uuidToVoiceMap.find(uuid);
		if (it != m_uuidToVoiceMap.end()) {
			auto voiceIt = std::find_if(m_voices.begin(), m_voices.end(),
				[&](const std::unique_ptr<dVoice>& v) { return v->getId() == uuid; });
			if (voiceIt != m_voices.end()) {
				size_t index = std::distance(m_voices.begin(), voiceIt);
				m_voices.erase(index);
				m_uuidToVoiceMap.erase(it);
			}
		}
	}

	dVoice* dEngine::getVoiceByUuid(const dUuid& uuid) const {
		auto it = m_uuidToVoiceMap.find(uuid);
		if (it != m_uuidToVoiceMap.end()) {
			return it->second;
		}
		return nullptr;
	}

	void dEngine::addOscilloscope(dOscilloscope* oscilloscope) {
		m_oscilloscope = oscilloscope;
	}

	float dEngine::generateSample() {
		float sample = 0.0f;
		for (auto& voice : m_voices) {
			sample += voice->generateSample();
		}

		m_sample = sample / m_voices.getSize(); // mix samples 
		
		if (m_oscilloscope != nullptr) {
			m_oscilloscope->addSample(m_sample);
			// DB_INFO("sample added to oscilloscope , {}", m_sample);
		}
		
		return m_sample;
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

		float* buffer = static_cast<float*>(outputBuffer);

		for (unsigned int i = 0; i < nBufferFrames; ++i) {
			float sample = engine->generateSample();
			for (unsigned int j = 0; j < engine->m_channels; ++j) {
				*buffer++ = sample; // Output the same sample to all channels
			}
		}

		return 0;
	}
}