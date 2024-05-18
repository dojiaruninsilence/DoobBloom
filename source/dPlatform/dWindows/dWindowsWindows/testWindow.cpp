#include "dbpch.h"

#include "testWindow.h"
#include "dBaseWindow.h"

#include "dRenderer/dGladInit.h"

#include "dUtils/dDiagnostics/dEventTesting.h"

#include <glad/glad.h>

namespace doob {
    dBaseWindow testWindow(400, 400, "bloom");
    dBaseWindow testWindow2(400, 800, "2bloom");

	void createTestWindow() {
        testWindow.baseWindowCreate(true);
        testWindow2.baseWindowCreate(false);

        glfwSetKeyCallback(testWindow.getWindow(), key_callback);
        glfwSetKeyCallback(testWindow2.getWindow(), key_callback);

        initializeGlad();
	}

    bool testWindowShouldClose() {
        return glfwWindowShouldClose(testWindow.getWindow());
    }

    void testWindowPoll() {
        glfwPollEvents();
    }

    void testWindowSwapBuffer() {
        glfwMakeContextCurrent(testWindow.getWindow());
        int display_w, display_h;
        glfwGetFramebufferSize(testWindow.getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.25f, 0.75f, 0.20f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(testWindow.getWindow());

        if (!glfwWindowShouldClose(testWindow2.getWindow())) {
            glfwMakeContextCurrent(testWindow2.getWindow());
            glfwGetFramebufferSize(testWindow2.getWindow(), &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.15f, 0.85f, 0.10f, 1.00f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(testWindow2.getWindow());
        }
    }
}