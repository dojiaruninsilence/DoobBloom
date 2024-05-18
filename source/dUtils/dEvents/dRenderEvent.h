#pragma once

#include "dEvent.h"

namespace doob {

	class dRenderEvent : public dEvent {
	public:
		dRenderEvent() {}

		EVENT_CLASS_TYPE(rendRender)
		EVENT_CLASS_CATEGORY(render)
	};
}