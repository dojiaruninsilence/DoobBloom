#include "dbpch.h"

#include "testWindow.h"
#include "dBaseWindow.h"

#include "dRenderer/dGladInit.h"

#include "dUI/dImgui/dImguiInit.h"

#include "dUtils/dDiagnostics/dEventTesting.h"

#include "dUtils/dRenderUtils/dColors.h"

#include <glad/glad.h>
#include <imgui.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace doob {
    std::unique_ptr<dBaseWindow> testWindow;
    //dBaseWindow testWindow(400, 400, "bloom");
    //dBaseWindow testWindow2(400, 800, "2bloom");

	void createTestWindow() {
        testWindow = std::make_unique<dBaseWindow>(400, 400, "bloom");
        testWindow->baseWindowCreate(true);
        //testWindow2.baseWindowCreate(false);

        glfwSetKeyCallback(testWindow->getWindow(), key_callback);
        //glfwSetKeyCallback(testWindow2.getWindow(), key_callback);

        initializeGlad();
        initializeImgui();

        ImGui_ImplGlfw_InitForOpenGL(testWindow->getWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 130");

        //ImGui_ImplGlfw_InitForOpenGL(testWindow2.getWindow(), true);
	}

    bool testWindowShouldClose() {
        return glfwWindowShouldClose(testWindow->getWindow());
    }

    void testWindowPoll() {
        glfwPollEvents();
    }

    void testWindowSwapBuffer() {
        glfwMakeContextCurrent(testWindow->getWindow());
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        //// Render your ImGui UI for the first window
        //ImGui::Begin("Window 1");
        //ImGui::Text("Hello from Window 1");
        //ImGui::End();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(testWindow->getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        dGlClearColor(dColors::olive);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(testWindow->getWindow());

       // if (!glfwWindowShouldClose(testWindow2.getWindow())) {
            //glfwMakeContextCurrent(testWindow2.getWindow());
            //ImGui_ImplOpenGL3_NewFrame();
            //ImGui_ImplGlfw_NewFrame();
            //ImGui::NewFrame();

            //// Render your ImGui UI for the second window
            //ImGui::Begin("Window 2");
            //ImGui::Text("Hello from Window 2");
            //ImGui::End();

            //ImGui::Render();
           // glfwGetFramebufferSize(testWindow2.getWindow(), &display_w, &display_h);
            //glViewport(0, 0, display_w, display_h);
            //dGlClearColor(dColors::yellowGreen);
            //glClear(GL_COLOR_BUFFER_BIT);
            //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
           // glfwSwapBuffers(testWindow2.getWindow());
       // }
    }
}