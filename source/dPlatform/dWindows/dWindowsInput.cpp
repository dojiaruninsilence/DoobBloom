#include "dbpch.h"

#include "dWindowsInput.h"

namespace doob {

	void dWindowsInput::init() {
		DB_TRACE_QUIET("windows input system initialized");
	}

	void dWindowsInput::shutdown() {
		DB_TRACE_QUIET("windows input system shutdown");
	}

	bool dWindowsInput::isKeyPressed(const keyCode key) {
		return (GetAsyncKeyState(static_cast<int>(key)) & 0x8000) != 0;
	}

	bool dWindowsInput::isMouseButtonPressed(const mouseCode key) {
		return false;
	}

	dMath::dVec2<float> dWindowsInput::getMousePosition() {
		return 0;
	}
}