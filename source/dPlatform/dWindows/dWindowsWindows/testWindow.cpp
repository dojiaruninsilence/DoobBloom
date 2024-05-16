#include "dbpch.h"

#include "testWindow.h"
#include "dBaseWindow.h"


namespace doob {
    dBaseWindow testWindow(400, 400, "bloom");

	void createTestWindow() {
		testWindow.baseWindowCreate();

        //while (!glfwWindowShouldClose(testWindow.getWindow())) {
        //    // Poll for and process events
        //    glfwPollEvents();

        //    // Rendering commands here (if any)

        //    // Swap buffers
        //    glfwSwapBuffers(testWindow.getWindow());
        //}
	}

    bool testWindowShouldClose() {
        return glfwWindowShouldClose(testWindow.getWindow());
    }

    void testWindowPoll() {
        glfwPollEvents();
    }

    void testWindowSwapBuffer() {
        glfwSwapBuffers(testWindow.getWindow());
    }
}