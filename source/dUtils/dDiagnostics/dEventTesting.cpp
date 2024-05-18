#include "dbpch.h"

#include "dEventTesting.h"

namespace doob {
	void handleEvent(dEvent& event);

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			dKeyPressedEvent keyPressedEvent(key, 0);
			handleEvent(keyPressedEvent);
		} else if (action == GLFW_RELEASE) {
			dKeyReleasedEvent keyReleasedEvent(key);
			handleEvent(keyReleasedEvent);
		}
	}

	void handleEvent(dEvent& event) {
		dEventDispatcher dispatcher(event);
		dispatcher.dispatch<dKeyPressedEvent>([](dKeyPressedEvent& e) {
			DB_INFO(e.toString());
			return true;
		});

		dispatcher.dispatch<dKeyReleasedEvent>([](dKeyReleasedEvent& e) {
			DB_INFO(e.toString());
			return true;
		});
	}
}