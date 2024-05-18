#pragma once

#include "dCore/dCoreConfig.h"

#include <functional>
#include <string>

namespace doob {

	enum class eventType {
		none = 0,
		windowClose, windowResize, windowFocus, windowLostFocus, windowMoved,
		appTick, appUpdate, 
		rendRender,
		keyPressed, keyReleased, keyTyped,
		mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScrolled
	};

	enum eventCategory {
		none = 0,
		application = BIT(0),
		window = BIT(1),
		render = BIT(2),
		input = BIT(3),
		keyboard = BIT(4),
		mouse = BIT(5),
		mouseButton = BIT(6)
	};

#define EVENT_CLASS_TYPE(type) static eventType getStaticType() { return eventType::##type; }\
																virtual eventType getEventType() const override { return getStaticType(); }\
																virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class dEvent {
		friend class dEventDispatcher;
	public:
		bool m_handled = false;

		virtual eventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(eventCategory category) {
			return getCategoryFlags() & category;
		}
	};

	class dEventDispatcher {
		template <typename Type>
		using eventFn = std::function<bool(Type&)>;
	public:
		dEventDispatcher(dEvent& event)
			: m_event(event) {
		}

		template <typename Type>
		bool dispatch(eventFn<Type> func) {
			if (m_event.getEventType() == Type::getStaticType()) {
				m_event.m_handled = func(*(Type*)&m_event);
				return true;
			}
			return false;
		}

	private:
		dEvent& m_event;
	};
}