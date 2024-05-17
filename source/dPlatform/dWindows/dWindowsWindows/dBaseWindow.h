#pragma once

#include <GLFW/glfw3.h>

namespace doob {

	//void mainWindowCloseCallback(GLFWwindow* window);

	//void secondaryWindowCloseCallback(GLFWwindow* window);

	class dBaseWindow {
	public:

		dBaseWindow(int width, int height, const char* name);

		~dBaseWindow();


		bool baseWindowCreate(bool main);

		GLFWwindow* getWindow() { return window; }
	private:
		int width;
		int height;
		const char* name;
		GLFWwindow* window;
	};
}