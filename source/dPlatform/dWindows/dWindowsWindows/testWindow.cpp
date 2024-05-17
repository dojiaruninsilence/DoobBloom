#include "dbpch.h"

#include "testWindow.h"
#include "dBaseWindow.h"


namespace doob {
    dBaseWindow testWindow(400, 400, "bloom");
    dBaseWindow testWindow2(400, 800, "2bloom");

	void createTestWindow() {
        testWindow.baseWindowCreate(true);
        testWindow2.baseWindowCreate(false);
	}

    bool testWindowShouldClose() {
        return glfwWindowShouldClose(testWindow.getWindow());
    }

    void testWindowPoll() {
        glfwPollEvents();
    }

    void testWindowSwapBuffer() {
        glfwSwapBuffers(testWindow.getWindow());
        if (!glfwWindowShouldClose(testWindow2.getWindow())) {
            glfwSwapBuffers(testWindow2.getWindow());
        }
    }
}