#include "dbpch.h"

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <imgui.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_glfw.cpp>

int main() {
	// test
	std::cout << "Lets bring flowers to the world!" << std::endl;

    dDiagnostics::dLog::Init();

    DB_TRACE("Lets bring flowers");
    DB_INFO("Lets bring flowers");
    DB_WARN("Lets bring flowers");
    DB_ERROR("Lets bring flowers");
    DB_FATAL("Lets bring flowers");

    DB_TRACE_QUIET("Lets bring flowers");
    DB_INFO_QUIET("Lets bring flowers");
    DB_WARN_QUIET("Lets bring flowers");
    DB_ERROR_QUIET("Lets bring flowers");
    DB_FATAL_QUIET("Lets bring flowers");

    // Example of reporting an error
    dDiagnostics::reportError(dDiagnostics::errorLevel::D_INFO, dDiagnostics::errorCode::RUNTIME_ERROR, "Invalid input", __FILE__, __LINE__);
    dDiagnostics::reportError(dDiagnostics::errorLevel::D_WARNING, dDiagnostics::errorCode::RUNTIME_ERROR, "Invalid input", __FILE__, __LINE__);
    dDiagnostics::reportError(dDiagnostics::errorLevel::D_ERROR, dDiagnostics::errorCode::RUNTIME_ERROR, "Invalid input", __FILE__, __LINE__);
    //dDiagnostics::reportError(dDiagnostics::errorLevel::D_FATAL, dDiagnostics::errorCode::RUNTIME_ERROR, "Invalid input", __FILE__, __LINE__);

     // Test dVector with int type
    dMath::dVector<int> intVector;

    // Test push_back
    intVector.push_back(4);
    intVector.push_back(2);
    intVector.push_back(6);
    intVector.push_back(1);

    // Test min and max
    std::cout << "Minimum value in intVector: " << intVector.min() << std::endl;
    std::cout << "Maximum value in intVector: " << intVector.max() << std::endl;

    // Test dVector with double type
    dMath::dVector<double> doubleVector;

    // Test push_back
    doubleVector.push_back(3.5);
    doubleVector.push_back(1.5);
    doubleVector.push_back(2.5);
    doubleVector.push_back(4.5);

    // Test min and max
    std::cout << "Minimum value in doubleVector: " << doubleVector.min() << std::endl;
    std::cout << "Maximum value in doubleVector: " << doubleVector.max() << std::endl;


    
   
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;        // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Example: show a demo window
        ImGui::ShowDemoWindow();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}