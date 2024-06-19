#pragma once

#include "dUtils/dUuid.h"

namespace doob {
	class dSound {
	public:
		dSound() : m_id() {}

		virtual float generateSample() = 0;
		virtual void setFrequency(float freq) = 0;
		virtual void setSampleRate(float sr) = 0;

		const dUuid& getId() const {
			return m_id;
		}

		virtual ~dSound() = default;

	private:
		dUuid m_id;
	};
}