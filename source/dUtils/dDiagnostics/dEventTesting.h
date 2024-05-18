#pragma once

#include "dEvents/dEvent.h"
#include "dEvents/dKeyEvent.h"
#include "dDiagnostics/dLogger.h"

#include <GLFW/glfw3.h>

namespace doob {
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}