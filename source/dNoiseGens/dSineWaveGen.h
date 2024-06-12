#pragma once

#include "doobEngine/dSound.h"

#include "dUtils/dMath/dWaveforms/dSineWave.h"

namespace doob {
	class dSineWaveGen : public dSound {
	public:
		dSineWaveGen(float freq = 440.0f, float sr = 44100.0f);
		~dSineWaveGen() {}

		float generateSample() override;

		void setFrequency(float freq) override;
		void setSampleRate(float sr) override;
		void setAmplitude(float amp);

	private:
		double m_currentTime = 0.0;
		double m_phase;
		double m_frequency;
		double m_sampleRate;
		double m_phaseIncrement;
		double m_amplitude;

		dSineWave m_sineWaveGenerator;
	};
}