#pragma once

#include "dEvent.h"

#include <string>
#include <sstream>

namespace doob {

	class dKeyEvent : public dEvent {
	public:
		inline int getKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(keyboard | input)
	protected:
		dKeyEvent(int keycode)
			: m_keyCode(keycode) {}

		int m_keyCode;
	};

	class dKeyPressedEvent : public dKeyEvent {
	public:
		dKeyPressedEvent(int keycode, int repeatCount)
			: dKeyEvent(keycode), m_repeatCount(repeatCount) {}

		inline int getRepeatCount() const { return m_repeatCount; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "dKeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyPressed)
	private:
		int m_repeatCount;
	};

	class dKeyReleasedEvent : public dKeyEvent {
	public:
		dKeyReleasedEvent(int keycode)
			: dKeyEvent(keycode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "dKeyReleasedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyReleased)
	};

	class dKeyTypedEvent : public dKeyEvent {
	public:
		dKeyTypedEvent(int keycode)
			: dKeyEvent(keycode) {}

		inline int getRepeatCount() const { return m_repeatCount; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "dKeyTypedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyTyped)
	private:
		int m_repeatCount;
	};
}