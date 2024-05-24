#include "dbpch.h"

#include "dGenericPane.h"

#include <imgui.h>

namespace doob {

	void dGenericPane::genericPaneUpdate() {

		ImGui::Begin("testPane", NULL, ImGuiWindowFlags_NoTitleBar);
		ImGui::Text("Did it work");
		ImGui::End();
	}
}