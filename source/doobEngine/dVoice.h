#pragma once

#include "doobEngine/dSound.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <memory>

namespace doob {
	class dVoice {
	public:
		void addSound(std::unique_ptr<dSound> sound);
		void removeSound(size_t index);

		float generateSample();

		void setSampleRate(float sr);
		void setFrequency(float freq);
	private:
		dVector<std::unique_ptr<dSound>> sounds;
	};
}