#pragma once

#include <GLFW/glfw3.h>

namespace doob {

	//void mainWindowCloseCallback(GLFWwindow* window);

	//void secondaryWindowCloseCallback(GLFWwindow* window);

	class dBaseWindow {
	public:

		dBaseWindow();

		~dBaseWindow();


		bool baseWindowCreate(int width, int height, const char* name, bool main);

		GLFWwindow* getWindow() { return window; }
	private:
		GLFWwindow* window;
	};
}