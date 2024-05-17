#pragma once

//#include <GLFW/glfw3.h>

namespace doob {
	void glfwErrorCallback(int error, const char* description);

	bool initializeGlfw();

	void shutdownGlfw();
}