#include "dbpch.h"

#include "dVoice.h"

namespace doob {
	dVoice::dVoice() : m_id() {}

	void dVoice::addSound(std::unique_ptr<dSound> sound) {
		dUuid soundId = sound->getId();
		m_uuidToSoundMap[soundId] = sound.get();
		m_sounds.push_back(std::move(sound));
	}

	void dVoice::removeSound(const dUuid& uuid) {
		auto it = m_uuidToSoundMap.find(uuid);

		if (it != m_uuidToSoundMap.end()) {
			auto soundIt = std::find_if(m_sounds.begin(), m_sounds.end(),
				[&](const std::unique_ptr<dSound>& s) { return s->getId() == uuid; });

			if (soundIt != m_sounds.end()) {
				size_t index = std::distance(m_sounds.begin(), soundIt);
				m_sounds.erase(index);
				m_uuidToSoundMap.erase(it);
			}
		}
	}

	dSound* dVoice::getSoundByUuid(const dUuid& uuid) const {
		auto it = m_uuidToSoundMap.find(uuid);

		if (it != m_uuidToSoundMap.end()) {
			return it->second;
		}

		return nullptr;
	}

	float dVoice::generateSample() {
		float sample = 0.0f;
		for (auto& sound : m_sounds) {
			sample += sound->generateSample();
		}
		return sample / m_sounds.getSize(); // mix samples
	}

	void dVoice::setSampleRate(float sr) {
		for (auto& sound : m_sounds) {
			sound->setSampleRate(sr);
		}
	}

	void dVoice::setFrequency(float freq) {
		for (auto& sound : m_sounds) {
			sound->setFrequency(freq);
		}
	}

	const dUuid& dVoice::getId() const {
		return m_id;
	}
}