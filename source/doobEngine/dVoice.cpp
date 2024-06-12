#include "dbpch.h"

#include "dVoice.h"

namespace doob {
	void dVoice::addSound(std::unique_ptr<dSound> sound) {
		sounds.push_back(std::move(sound));
	}

	void dVoice::removeSound(size_t index) {
		if (index < sounds.getSize()); {
			sounds.erase(index);
		}
	}

	float dVoice::generateSample() {
		float sample = 0.0f;
		for (auto& sound : sounds) {
			sample += sound->generateSample();
		}
		return sample / sounds.getSize(); // mix samples
	}

	void dVoice::setSampleRate(float sr) {
		for (auto& sound : sounds) {
			sound->setSampleRate(sr);
		}
	}

	void dVoice::setFrequency(float freq) {
		for (auto& sound : sounds) {
			sound->setFrequency(freq);
		}
	}
}