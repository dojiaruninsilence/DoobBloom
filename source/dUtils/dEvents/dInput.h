#pragma once

#include "dUtils/dEvents/dKeyCodes.h"
#include "dUtils/dEvents/dMouseCodes.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

namespace doob {
	class dInput {
	public:
		virtual ~dInput() = default;

		virtual void init() {}

		virtual void shutdown() = 0;

		virtual bool isKeyPressed(keyCode key) = 0;

		virtual bool isMouseButtonPressed(mouseCode button) = 0;

		virtual dMath::dVec2<float> getMousePosition() = 0;
	};
}