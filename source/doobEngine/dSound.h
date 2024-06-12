#pragma once

namespace doob {
	class dSound {
	public:
		virtual float generateSample() = 0;
		virtual void setFrequency(float freq) = 0;
		virtual void setSampleRate(float sr) = 0;
		virtual ~dSound() = default;
	};
}