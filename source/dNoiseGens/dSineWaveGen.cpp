#include "dbpch.h"

#include "dSineWaveGen.h"

namespace doob {
	dSineWaveGen::dSineWaveGen(float freq, float sr)
		: m_frequency(freq), m_sampleRate(sr), m_phase(0.0f), m_amplitude(1.0f) {
		m_phaseIncrement = 1.0 / m_sampleRate;
	}

	float dSineWaveGen::generateSample() {
		float sample = m_sineWaveGenerator.generate(m_currentTime, m_frequency, m_amplitude, m_phase);
		m_currentTime += m_phaseIncrement;
		return sample;
	}

	void dSineWaveGen::setFrequency(float freq) {
		m_frequency = freq;
	}

	void dSineWaveGen::setSampleRate(float sr) {
		m_sampleRate = sr;
		m_phaseIncrement = 1.0 / m_sampleRate;
	}

	void dSineWaveGen::setAmplitude(float ampl) {
		m_amplitude = ampl;
	}
}