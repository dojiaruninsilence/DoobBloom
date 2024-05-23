#include "dbpch.h"

#include "dBaseWindow.h"


namespace doob {
    void mainWindowCloseCallback(GLFWwindow* window) {
        // Close the application if the main window is closed
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void secondaryWindowCloseCallback(GLFWwindow* window) {
        // Close only the secondary window
        glfwDestroyWindow(window);

    }

    dBaseWindow::dBaseWindow() {
        //DB_INFO("creating window: {0}", name);
    }

    dBaseWindow::~dBaseWindow() {
        if (window) {
            //glfwDestroyWindow(window);
            //glfwTerminate();
        }
    }

	bool dBaseWindow::baseWindowCreate(int width, int height, const char* name, bool main) {
        // Set GLFW window hints (optional)
        // For example, to use OpenGL 3.3 core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

        // Create a GLFW window
        window = glfwCreateWindow(width, height, name, NULL, NULL);
        if (!window)
        {
            // Window creation error will be reported by the error callback function
            glfwTerminate(); // Cleanup GLFW resources
            return false;
        }

        if (main) {
            glfwSetWindowCloseCallback(window, mainWindowCloseCallback);
        } else {
            glfwSetWindowCloseCallback(window, secondaryWindowCloseCallback);
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Enable vertical sync (optional)
        glfwSwapInterval(1);

        DB_INFO("creating window: {0}", name);
        return true;
	}
}