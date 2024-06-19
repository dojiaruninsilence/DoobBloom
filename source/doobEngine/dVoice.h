#pragma once

#include "doobEngine/dSound.h"

#include "dUtils/dUuid.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <memory>
#include <unordered_map>

namespace doob {
	class dVoice {
	public:
		dVoice();

		void addSound(std::unique_ptr<dSound> sound);
		void removeSound(const dUuid& uuid);

		dSound* getSoundByUuid(const dUuid& uuid) const;

		float generateSample();

		void setSampleRate(float sr);
		void setFrequency(float freq);

		const dUuid& getId() const;
	private:
		dVector<std::unique_ptr<dSound>> m_sounds;
		std::unordered_map<dUuid, dSound*> m_uuidToSoundMap;
		dUuid m_id;
	};
}