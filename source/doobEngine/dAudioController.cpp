#include "dbpch.h"
//
//#include "dAudioController.h"
//
//namespace doob {
//	dAudioController::dAudioController(unsigned int bufferSize) : m_engine(dEngine(bufferSize, 2)), m_bufferSize(bufferSize) {
//
//	}
//
//	dAudioController::~dAudioController() {
//
//	}
//
//	bool dAudioController::initialize() {
//		RtAudio::StreamParameters params;
//		params.deviceId = m_audio.getDefaultOutputDevice();
//		params.nChannels = m_engine.getChannels();
//		params.firstChannel = 0;
//
//		RtAudio::StreamOptions options;
//		options.flags = RTAUDIO_MINIMIZE_LATENCY;
//
//		m_audio.openStream(&params, nullptr, RTAUDIO_FLOAT32, 44100, &m_bufferSize, &audioCallback, this, &options);
//
//		return true;
//	}
//
//	void dAudioController::addVoiceToEngine(dEngine engine, std::unique_ptr<dVoice> voice) {
//		engine.addVoice(std::move(voice));
//	}
//
//	void dAudioController::removeVoice(dEngine engine, size_t index) {
//		engine.removeVoice(index);
//	}
//
//	void dAudioController::start() {
//		if (!m_audio.isStreamRunning()) {
//			m_audio.startStream();
//		}
//	}
//
//	void dAudioController::stop() {
//		if (!m_audio.isStreamRunning()) {
//			m_audio.stopStream();
//		}
//	}
//
//	int dAudioController::audioCallback(void* outputBuffer, void* inputBuffer,
//		unsigned int nBufferFrames, double streamTime,
//		RtAudioStreamStatus status, void* userData) {
//
//		float* buffer = static_cast<float*>(outputBuffer);
//
//		for (unsigned int i = 0; nBufferFrames; ++i) {
//			float sample = m_engine.generateSample();
//		}
//	}
//
//	void dAudioController::handleAudioCallback() {
//
//	}
//}