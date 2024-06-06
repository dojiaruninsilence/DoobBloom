#pragma once


#include "dUtils/dMath/dGeneralMath/dTrig.h"

namespace doob {

	class testSineGen {
	public:
		testSineGen(float frequency, float sampleRate)
			: m_frequency(frequency), m_sampleRate(sampleRate), m_phase(0.0f) {}

		float generateSample() {
			float sample = dTrig<float>::sin(2.0f * D_PI * m_phase);
			m_phase += m_frequency / m_sampleRate;
			if (m_phase >= 1.0f) {
				m_phase -= 1.0f;
			}
			return sample;
		}

	private:
		float m_frequency;
		float m_sampleRate;
		float m_phase;
	};
}