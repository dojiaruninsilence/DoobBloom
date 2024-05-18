#pragma once

#include "dEvent.h"

namespace doob {
	class dAppTickEvent : public dEvent {
	public:
		dAppTickEvent() {}

		EVENT_CLASS_TYPE(appTick)
		EVENT_CLASS_CATEGORY(application)
	};

	class dAppUpdateEvent : public dEvent {
		dAppUpdateEvent() {}

		EVENT_CLASS_TYPE(appUpdate)
		EVENT_CLASS_CATEGORY(application)
	};
}