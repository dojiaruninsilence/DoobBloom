#include "dbpch.h"

#include "dWinGlfwInit.h"

#include <GLFW/glfw3.h>

namespace doob {

    void glfwErrorCallback(int error, const char* description) {
        // get the proper error code and level from glfw codes
        dDiagnostics::errorLevel level;
        dDiagnostics::errorCode code;

        switch (error)
        {
        case GLFW_NOT_INITIALIZED:
        case GLFW_NO_CURRENT_CONTEXT:
            level = dDiagnostics::errorLevel::D_ERROR;
            code = dDiagnostics::errorCode::INITIALIZATION_ERROR;
            break;

        default:
            level = dDiagnostics::errorLevel::D_ERROR;
            code = dDiagnostics::errorCode::RUNTIME_ERROR;
            break;
        }

        // report the glfw error using the messaging system
        dDiagnostics::reportError(level, code, description, __FILE__, __LINE__);
    }

	bool initializeGlfw() {
        // set the error callback using our error system
        glfwSetErrorCallback(glfwErrorCallback);

        // initialize glfw
        if (!glfwInit())
        {
            // initialization error will be reported by the error callback function
            return false;
        }

        return true;
	}
}