#pragma once

#include "dUI/dOscilloscope/dOscilloscope.h"

#include "dUtils/dUuid.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <unordered_map>
#include <memory>

namespace doob {
	class dOscilloscopeManager {
	public:
		dOscilloscopeManager(size_t bufferSize);
		~dOscilloscopeManager();

		dUuid createOscilloscope();

		void removeOscilloscope(const dUuid& id);

		void addSample(const dUuid& id, float sample);

		const dVector<float>& getBuffer(const dUuid& id) const;

		dOscilloscope* getOscilloscope(const dUuid& id);

		void renderAllOscilloscopes();
	private:
		size_t m_bufferSize;
		std::unordered_map<dUuid, std::unique_ptr<dOscilloscope>> m_oscilloscopes;
	};
}