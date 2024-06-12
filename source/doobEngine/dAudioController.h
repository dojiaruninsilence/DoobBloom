#pragma once

//#include "RtAudio.h"
//
//#include "doobEngine/dEngine.h"
//
//namespace doob {
//	class dAudioController {
//	public:
//		dAudioController(unsigned int bufferSize);
//		~dAudioController();
//
//		bool initialize();
//
//		void addVoiceToEngine(dEngine engine, std::unique_ptr<dVoice> voice);
//		void removeVoice(dEngine engine, size_t index);
//
//		void start();
//		void stop();
//	private:
//		static int audioCallback(void* outputBuffer, void* inputBuffer,
//			unsigned int nBufferFrames, double streamTime,
//			RtAudioStreamStatus status, void* userData);
//
//		void handleAudioCallback(float* outputBuffer, unsigned int nBufferFrames);
//
//		RtAudio m_audio;
//		dEngine m_engine;
//		unsigned int m_bufferSize;
//	};
//}