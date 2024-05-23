#include "dbpch.h"

#include "dGenericFrame.h"

#include "dPlatform/dWindows/dWindowsWindows/dBaseWindow.h"

#include "dRenderer/dGladInit.h"

#include "dUI/dImgui/dImguiInit.h"

#include "dUtils/dDiagnostics/dEventTesting.h"

#include "dUtils/dRenderUtils/dColors.h"

#include <glad/glad.h>
#include <imgui.h>
//#include <imgui_internal.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace doob {

	std::unique_ptr<dBaseWindow> genericFrame;

	bool isFullscreen = false;
	int windowX, windowY, windowWidth, windowHeight;

	void toggleFullscreen(GLFWwindow* window) {
		isFullscreen = !isFullscreen;
		if (isFullscreen) {
			glfwGetWindowPos(window, &windowX, &windowY);
			glfwGetWindowSize(window, &windowWidth, &windowHeight);

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else {
			glfwSetWindowMonitor(window, nullptr, windowX, windowY, windowWidth, windowHeight, 0);
		}
	}

	void dGenericFrame::createGenericFrame() {
		genericFrame = std::make_unique<dBaseWindow>();
		genericFrame->baseWindowCreate(m_width, m_height, m_name, true);

		initializeGlad();
		initializeImgui();

		ImGui_ImplGlfw_InitForOpenGL(genericFrame->getWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	bool dGenericFrame::genericFrameShouldClose() {
		return glfwWindowShouldClose(genericFrame->getWindow());
	}

	void dGenericFrame::genericFrameUpdateBegin() {
		glfwMakeContextCurrent(genericFrame->getWindow());
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGuiIO& io = ImGui::GetIO();
		
		// Begin a full-screen, borderless window
		glfwGetWindowPos(genericFrame->getWindow(), &m_xPos, &m_yPos);
		glfwGetWindowSize(genericFrame->getWindow(), &m_width, &m_height);

		ImVec2 mousePos = ImGui::GetMousePos();

		const int border = 8;
		const int titleBarHeight = 30;

		dVec2<int> leftHandleMin = dVec2<int>(m_xPos, m_yPos + titleBarHeight);
		dVec2<int> leftHandleMax = dVec2<int>(m_xPos + border, m_yPos + m_height - titleBarHeight);

		dVec2<int> rightHandleMin = dVec2<int>(m_xPos + m_width - border, m_yPos + titleBarHeight);
		dVec2<int> rightHandleMax = dVec2<int>(m_xPos + m_width, m_yPos + m_height - titleBarHeight);

		dVec2<int> bottomHandleMin = dVec2<int>(m_xPos, m_yPos + m_height - border);
		dVec2<int> bottomHandleMax = dVec2<int>(m_xPos + m_width, m_yPos + m_height);

		dVec2<int> leftCornerHandleMin = dVec2<int>(m_xPos, m_yPos + m_height - border);
		dVec2<int> leftCornerHandleMax = dVec2<int>(m_xPos + border, m_yPos + m_height);

		dVec2<int> rightCornerHandleMin = dVec2<int>(m_xPos + m_width - border, m_yPos + m_height - border);
		dVec2<int> rightCornerHandleMax = dVec2<int>(m_xPos + m_width, m_yPos + m_height);

		ImGui::SetNextWindowPos(ImVec2(m_xPos, m_yPos));
		ImGui::SetNextWindowSize(ImVec2(m_width, m_height));
		ImGui::Begin("Main", NULL, 
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground | 
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | 
			ImGuiWindowFlags_NoDocking);

		ImGui::PushStyleColor(ImGuiCol_ChildBg, dImVec4Color(dColors::darkOlive));

		// Custom Title Bar
		ImGui::SetNextWindowPos(ImVec2(m_xPos, m_yPos));
		ImGui::BeginChild("TitleBar", ImVec2(m_width, m_height), true, ImGuiWindowFlags_NoTitleBar | 
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | 
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking);

		// Handle dragging
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {

			if (!m_titleDrag) {
				m_titleDrag = true;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowPos = dVec2<float>(m_xPos, m_yPos);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);
			glfwSetWindowPos(genericFrame->getWindow(), static_cast<int>(m_initialWindowPos.x + m_mouseDelta.x), static_cast<int>(m_initialWindowPos.y + m_mouseDelta.y));
		} else {
			m_titleDrag = false;
		}

		ImGui::Text("Custom Title Bar");

		// Fullscreen Toggle Button
		ImGui::SameLine(ImGui::GetWindowWidth() - 203); // Adjust the position
		if (ImGui::Button("Fullscreen")) {
			toggleFullscreen(genericFrame->getWindow());
		}

		// Minimize Button
		ImGui::SameLine(ImGui::GetWindowWidth() - 120);
		if (ImGui::Button("Minimize")) {
			glfwIconifyWindow(genericFrame->getWindow());
		}

		ImGui::SameLine(io.DisplaySize.x - 50);
		if (ImGui::Button("Close")) {
			glfwSetWindowShouldClose(genericFrame->getWindow(), GLFW_TRUE);
		}
		ImGui::EndChild();

		// left handle resizing functionality
		ImGui::SetNextWindowPos(ImVec2(leftHandleMin.x, leftHandleMin.y));
		ImGui::BeginChild("leftHandle", ImVec2(border, m_height), true, 
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | 
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking);

		if (mousePos.x >= leftHandleMin.x && mousePos.x <= leftHandleMax.x &&
			mousePos.y >= leftHandleMin.y && mousePos.y <= leftHandleMax.y) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
			DB_INFO("did it work");
		}

		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			if (!m_leftEdgeDrag) {
				m_leftEdgeDrag = true;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowPos = dVec2<float>(m_xPos, m_yPos);
				m_initialWindowSize = dVec2<float>(m_width, m_height);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);

			glfwSetWindowPos(genericFrame->getWindow(), static_cast<int>(m_initialWindowPos.x + m_mouseDelta.x), static_cast<int>(m_initialWindowPos.y));
			glfwSetWindowSize(genericFrame->getWindow(), static_cast<int>(m_initialWindowSize.x - m_mouseDelta.x), static_cast<int>(m_initialWindowSize.y));
		}
		else {
			m_leftEdgeDrag = false;
		}

		ImGui::EndChild();

		// right handle resizing funtionality
		ImGui::SetNextWindowPos(ImVec2(rightHandleMin.x, rightHandleMin.y));
		ImGui::BeginChild("rightHandle", ImVec2(border, m_height), true,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking);

		if (mousePos.x >= rightHandleMin.x && mousePos.x <= rightHandleMax.x &&
			mousePos.y >= rightHandleMin.y && mousePos.y <= rightHandleMax.y) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
			DB_INFO("did it work");
		}

		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			if (!m_rightEdgeDrag) {
				m_rightEdgeDrag = true;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowSize = dVec2<float>(m_width, m_height);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);

			glfwSetWindowSize(genericFrame->getWindow(), static_cast<int>(m_initialWindowSize.x + m_mouseDelta.x), 
				static_cast<int>(m_initialWindowSize.y));
		}
		else {
			m_rightEdgeDrag = false;
		}

		ImGui::EndChild();

		// bottom handle resizing funtionality
		ImGui::SetNextWindowPos(ImVec2(bottomHandleMin.x, bottomHandleMin.y));
		ImGui::BeginChild("bottomHandle", ImVec2(m_width, border), true,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking);

		if (mousePos.x >= bottomHandleMin.x && mousePos.x <= bottomHandleMax.x &&
			mousePos.y >= bottomHandleMin.y && mousePos.y <= bottomHandleMax.y) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
			DB_INFO("did it work");
		}

		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			if (!m_bottomDrag) {
				m_bottomDrag = true;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowSize = dVec2<float>(m_width, m_height);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);

			glfwSetWindowSize(genericFrame->getWindow(), static_cast<int>(m_initialWindowSize.x),
				static_cast<int>(m_initialWindowSize.y + m_mouseDelta.y));
		}
		else {
			m_bottomDrag = false;
		}

		ImGui::EndChild();

		// bottom left handle resizing funtionality
		ImGui::SetNextWindowPos(ImVec2(leftCornerHandleMin.x, leftCornerHandleMin.y));
		ImGui::BeginChild("leftCornerHandle", ImVec2(border, border), true,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking);

		if (mousePos.x >= leftCornerHandleMin.x && mousePos.x <= leftCornerHandleMax.x &&
			mousePos.y >= leftCornerHandleMin.y && mousePos.y <= leftCornerHandleMax.y) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);
			DB_INFO("did it work");
		}

		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			if (!m_leftCornerDrag) {
				m_leftCornerDrag = true;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowPos = dVec2<float>(m_xPos, m_yPos);
				m_initialWindowSize = dVec2<float>(m_width, m_height);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);

			glfwSetWindowPos(genericFrame->getWindow(), static_cast<int>(m_initialWindowPos.x + m_mouseDelta.x), 
				static_cast<int>(m_initialWindowPos.y));
			glfwSetWindowSize(genericFrame->getWindow(), static_cast<int>(m_initialWindowSize.x - m_mouseDelta.x),
				static_cast<int>(m_initialWindowSize.y + m_mouseDelta.y));
		}
		else {
			m_leftCornerDrag = false;
		}

		ImGui::EndChild();

		// bottom right handle resizing funtionality
		ImGui::SetNextWindowPos(ImVec2(rightCornerHandleMin.x, rightCornerHandleMin.y));
		ImGui::BeginChild("rightCornerHandle", ImVec2(border, border), true,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking);

		if (mousePos.x >= rightCornerHandleMin.x && mousePos.x <= rightCornerHandleMax.x &&
			mousePos.y >= rightCornerHandleMin.y && mousePos.y <= rightCornerHandleMax.y) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);
			DB_INFO("did it work");
		}

		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			if (!m_rightCornerDrag) {
				m_rightCornerDrag = true;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowSize = dVec2<float>(m_width, m_height);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);

			glfwSetWindowSize(genericFrame->getWindow(), static_cast<int>(m_initialWindowSize.x + m_mouseDelta.x),
				static_cast<int>(m_initialWindowSize.y + m_mouseDelta.y));
		}
		else {
			m_rightCornerDrag = false;
		}

		ImGui::EndChild();

		ImGui::PopStyleColor();

		// Rest of the window content
		ImGui::Text("Main content area");

		
		// right edge resize handle
		// bottom edge resize handle


		ImGui::End();

		// Begin the main content window
		ImGui::PushStyleColor(ImGuiCol_WindowBg, dImVec4Color(dColors::olive));
		ImGui::SetNextWindowPos(ImVec2(m_xPos + border, m_yPos + titleBarHeight));
		ImGui::SetNextWindowSize(ImVec2(m_width - (border * 2), m_height - (titleBarHeight + border)));
		ImGui::Begin("Main Window", NULL, 
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | 
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | 
			ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Text("Main content area");

		ImGui::End();

		ImGui::PopStyleColor();

		ImGui::ShowDemoWindow();
	}

	void dGenericFrame::genericFrameUpdateEnd() {
		ImGui::Render();
		glfwGetFramebufferSize(genericFrame->getWindow(), &m_fbWidth, &m_fbHeight);
		glViewport(0, 0, m_fbWidth, m_fbHeight);
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

		glfwSwapBuffers(genericFrame->getWindow());

		glfwPollEvents();
	}

	void dGenericFrame::genericFrameShutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(genericFrame->getWindow());
	}
}