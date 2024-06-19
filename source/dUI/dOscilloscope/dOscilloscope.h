#pragma once

#include "dUtils/dUuid.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include "dUtils/dMemory/dCircularBuffer.h"

namespace doob {
	class dOscilloscope {
	public:
		dOscilloscope(size_t bufferSize);
		~dOscilloscope();

		const dUuid& getId() const;

		void addSample(float sample);

		const dVector<float>& getBuffer() const;

		void printBuffer() const;

		void render() const;

	private:
		dCircularBuffer<float> m_buffer;
		dUuid m_id;
	};
}