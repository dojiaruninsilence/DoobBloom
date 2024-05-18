#include "dbpch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace doob {
	void initializeGlad() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			DB_FATAL("failed to create GLFW window");
		}
	}
}