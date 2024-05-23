#include "dbpch.h"

#include "testFrame.h"

#include "dPlatform/dWindows/dWindowsWindows/dBaseWindow.h"

#include "dRenderer/dGladInit.h"

#include "dUI/dImgui/dImguiInit.h"

#include "dUtils/dDiagnostics/dEventTesting.h"

#include "dUtils/dRenderUtils/dColors.h"

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_internal.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace doob {

	std::unique_ptr<dBaseWindow> dtestFrame;

	void testFrame::createTestFrame() {
		dtestFrame = std::make_unique<dBaseWindow>();
		dtestFrame->baseWindowCreate(m_width, m_height, m_name, true);

		initializeGlad();
		initializeImgui();

		ImGui_ImplGlfw_InitForOpenGL(dtestFrame->getWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	bool testFrame::testFrameShouldClose() {
		return glfwWindowShouldClose(dtestFrame->getWindow());
	}

	void testFrame::testFrameUpdateBegin() {
		glfwMakeContextCurrent(dtestFrame->getWindow());
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/*if (m_nextWidth == NULL) {
			m_nextWidth = m_width;
		}

		if (m_nextHeight == NULL) {
			m_nextHeight = m_height;
		}*/

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		ImGuiIO& io = ImGui::GetIO();

		// Begin a full-screen, borderless window
		glfwGetWindowPos(dtestFrame->getWindow(), &m_windowXPos, &m_windowYPos);
		glfwGetWindowSize(dtestFrame->getWindow(), &m_windowWidth, &m_windowHeight);
		ImGui::SetNextWindowPos(ImVec2(m_windowXPos, m_windowYPos));
		ImGui::SetNextWindowSize(ImVec2(m_windowWidth, m_windowHeight));
		ImGui::Begin("Main", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDocking);
		ImVec2 mousePos = ImGui::GetMousePos();

		dVec2<int> leftHandleMin = dVec2<int>(m_windowXPos, m_windowYPos + 30);
		dVec2<int> leftHandleMax = dVec2<int>(m_windowXPos + 10, m_windowYPos + m_windowHeight - 10);

		ImGui::PushStyleColor(ImGuiCol_ChildBg, dImVec4Color(dColors::darkOlive));

		ImGui::SetNextWindowPos(ImVec2(m_windowXPos, m_windowYPos));
		ImGui::BeginChild("titleBar", ImVec2(m_windowWidth, 30), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDocking);
		//		
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			if (!m_titleDrag) {
				m_titleDrag = true;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowPos = dVec2<float>(m_windowXPos, m_windowYPos);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);
			glfwSetWindowPos(dtestFrame->getWindow(), static_cast<int>(m_initialWindowPos.x + m_mouseDelta.x), static_cast<int>(m_initialWindowPos.y + m_mouseDelta.y));
		} else {
			m_titleDrag = false;
		}
		ImGui::EndChild();
		
		ImGui::SetNextWindowPos(ImVec2(leftHandleMin.x, leftHandleMin.y));
		ImGui::BeginChild("leftHandle", ImVec2(10, m_windowHeight), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | /*ImGuiWindowFlags_NoBringToFrontOnFocus |*/
			/*ImGuiWindowFlags_NoBackground |*/ ImGuiWindowFlags_NoScrollbar/* | ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoDocking);
		//
		//ImGui::Button("##testButton", ImVec2(10, m_windowHeight));
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(m_windowXPos, m_windowYPos), ImVec2(m_windowXPos + 10, m_windowYPos + m_windowHeight), IM_COL32(255, 0, 0, 255));
		if (mousePos.x >= leftHandleMin.x && mousePos.x <= leftHandleMax.x &&
			mousePos.y >= leftHandleMin.y && mousePos.y <= leftHandleMax.y) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
			DB_INFO("did it work");
		}

		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			if (!m_leftEdgeDrag) {
				m_leftEdgeDrag = true;

				m_counter = 0;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowPos = dVec2<float>(m_windowXPos, m_windowYPos);
				m_initialWindowSize = dVec2<float>(m_windowWidth, m_windowHeight);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);
			
			glfwSetWindowSize(dtestFrame->getWindow(), static_cast<int>(m_initialWindowSize.x - m_mouseDelta.x), static_cast<int>(m_initialWindowSize.y));
			glfwSetWindowPos(dtestFrame->getWindow(), static_cast<int>(m_initialWindowPos.x + m_mouseDelta.x), static_cast<int>(m_initialWindowPos.y));

			// add a timer, so that this is not called every frame
			
			/*m_nextWidth = static_cast<int>(m_initialWindowSize.x - m_mouseDelta.x);
			m_nextHeight = static_cast<int>(m_initialWindowSize.y);*/
			if (m_counter < 1) {
				m_counter++;
			}
			else if (m_counter >= 1) {
				
				m_counter = 0;
			}
						
			//glfwGetWindowSize(dtestFrame->getWindow(), &m_windowWidth, &m_windowHeight);
		}
		else {
			m_leftEdgeDrag = false;
		}
		ImGui::EndChild();

		ImGui::SetNextWindowPos(ImVec2(m_windowXPos + m_windowWidth - 10, m_windowYPos + 30.0f));
		ImGui::BeginChild("rightHandle", ImVec2(10, m_height), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDocking);
		//
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			if (!m_rightEdgeDrag) {
				m_rightEdgeDrag = true;

				m_initialMousePos = dVec2<float>(io.MousePos.x, io.MousePos.y);
				m_initialWindowSize = dVec2<float>(m_windowWidth, m_windowHeight);
			}
			m_mouseDelta = dVec2<float>(io.MousePos.x - m_initialMousePos.x, io.MousePos.y - m_initialMousePos.y);
			glfwSetWindowSize(dtestFrame->getWindow(), static_cast<int>(m_initialWindowSize.x + m_mouseDelta.x), static_cast<int>(m_initialWindowSize.y));
			//glfwGetWindowSize(dtestFrame->getWindow(), &m_windowWidth, &m_windowHeight);
		}
		else {
			m_rightEdgeDrag = false;
		}
		ImGui::EndChild();

		ImGui::SetNextWindowPos(ImVec2(m_windowXPos, m_windowYPos + m_windowHeight - 10));
		ImGui::BeginChild("bottomHandle", ImVec2(m_windowWidth, 10), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDocking);
		//
		ImGui::EndChild();

		

		ImGui::PopStyleColor();

		// Rest of the window content
		// ImGui::Text("Main content area");

		ImGui::End();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, dImVec4Color(dColors::olive));
		//glfwGetWindowSize(dtestFrame->getWindow(), &m_windowWidth, &m_windowHeight);
		ImGui::SetNextWindowPos(ImVec2(m_windowXPos + 10, m_windowYPos + 30));
		ImGui::SetNextWindowSize(ImVec2(m_windowWidth - 20, m_windowHeight - 40));
		ImGui::Begin("Main Window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | /*ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoBackground |*/ ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize/* | ImGuiWindowFlags_DockNodeHost*/);

		ImGui::Text("Main content area");

		ImGui::End();

		ImGui::PopStyleColor();

		ImGui::ShowDemoWindow();
	}

	void testFrame::testFrameUpdateEnd() {
		ImGui::Render();
		glfwGetFramebufferSize(dtestFrame->getWindow(), &m_fbWidth, &m_fbHeight);
		glViewport(0, 0, m_fbWidth, m_fbHeight);
		dGlClearColor(dColors::darkOlive);
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

		glfwSwapBuffers(dtestFrame->getWindow());

		glfwPollEvents();
	}

	void testFrame::testFrameShutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(dtestFrame->getWindow());
	}
}