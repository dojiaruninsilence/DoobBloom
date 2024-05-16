#include "dbpch.h"

#include "dBaseWindow.h"


namespace doob {
    dBaseWindow::dBaseWindow(int width, int height, const char* name)
        : window(nullptr), name(name), width(width), height(height) {
    }

    dBaseWindow::~dBaseWindow() {
        if (window) {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }

	bool dBaseWindow::baseWindowCreate() {
        // Set GLFW window hints (optional)
        // For example, to use OpenGL 3.3 core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a GLFW window
        window = glfwCreateWindow(1280, 720, "DoobBloom", NULL, NULL);
        if (!window)
        {
            // Window creation error will be reported by the error callback function
            glfwTerminate(); // Cleanup GLFW resources
            return false;
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Enable vertical sync (optional)
        glfwSwapInterval(1);

        return true;
	}
}