#pragma once

#include "dUtils/dMath/dGeneralMath/dVector.h"

#include <glad/glad.h>
#include <imgui.h>

namespace doob {

	struct dColor {
		dVec4<float> rgba;

		dColor(float r, float g, float b, float a = 1.0f)
			: rgba(r, g, b, a) {}

		dColor(dVec4<float> vec) : rgba(vec) {}
	};

	namespace dColors {
		const dColor olive(0.5f, 0.5f, 0.0f, 1.0f);
		const dColor darkOlive(0.33f, 0.42f, 0.18f, 1.0f);
		const dColor yellowGreen(0.6f, 0.8f, 0.2f, 1.0f);
	}

	void dGlClearColor(const dColor& color) {
		glClearColor(color.rgba.x, color.rgba.y, color.rgba.z, color.rgba.w);
	}

	ImVec4 dImVec4Color(const dColor& color) {
		ImVec4 outColor = ImVec4(color.rgba.x, color.rgba.y, color.rgba.z, color.rgba.w);
		return outColor;
	}
}