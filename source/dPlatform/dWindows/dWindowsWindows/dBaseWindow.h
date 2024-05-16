#pragma once

#include <GLFW/glfw3.h>

namespace doob {

	class dBaseWindow {
	public:

		dBaseWindow(int width, int height, const char* name);

		~dBaseWindow();

		bool baseWindowCreate();

		GLFWwindow* getWindow() { return window; }
	private:
		int width;
		int height;
		const char* name;
		GLFWwindow* window;
	};
}