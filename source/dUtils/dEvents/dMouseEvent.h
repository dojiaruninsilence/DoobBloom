#pragma once

#include "dEvent.h"

#include <string>
#include <sstream>

namespace doob {

	class dMouseMovedEvent : public dEvent {
	public:
		dMouseMovedEvent(float x, float y)
			: m_mouseX(x), m_mouseY(y) {}

		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "dMouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseMoved)
		EVENT_CLASS_CATEGORY(mouse | input)
	private:
		float m_mouseX, m_mouseY;
	};

	class dMouseScrolledEvent : public dEvent {
	public:
		dMouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float getXOffset() const { return m_xOffset; }
		inline float getYOffset() const { return m_yOffset; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "dMouseScrollEvent: " << getXOffset() << ", " << getYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseScrolled)
		EVENT_CLASS_CATEGORY(mouse | input)
	private:
		float m_xOffset, m_yOffset;
	};

	class dMouseButtonEvent : public dEvent {
	public:
		inline int getMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(mouse | input)
	protected:
		dMouseButtonEvent(int button)
			: m_button(button) {}

		int m_button;
	};

	class dMouseButtonPressedEvent : public dMouseButtonEvent {
	public:
		dMouseButtonPressedEvent(int button)
			: dMouseButtonEvent(button) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "dMouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseButtonPressed)
	};

	class dMouseButtonReleasedEvent : public dMouseButtonEvent {
	public:
		dMouseButtonReleasedEvent(int button)
			: dMouseButtonEvent(button) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "dMouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseButtonReleased)
	};
}