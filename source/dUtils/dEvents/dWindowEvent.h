#pragma once

#include "dEvent.h"

#include <string>
#include <sstream>

namespace doob {

	class dWindowResizeEvent : public dEvent {
	public:
		dWindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height) {}

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "dWindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(windowResize)
		EVENT_CLASS_CATEGORY(window)

	private:
		unsigned int m_width, m_height;
	};

	class dWindowCloseEvent : public dEvent {
	public:
		dWindowCloseEvent() {}

		EVENT_CLASS_TYPE(windowClose)
		EVENT_CLASS_CATEGORY(window)
	};
}