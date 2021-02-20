#pragma once

#include "Event.h"

namespace Neural {

	/*
	Parent class for all keyboard events 
	cant't be constructed
	*/
	class NEURAL_API KeyEvent
		: public Event {

	public:
		inline int getKeyCode() const {
			return m_keyCode;
		}
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode)
			: m_keyCode(keycode) {}

		int m_keyCode;
	};

	class NEURAL_API KeyPressedEvent
		: public KeyEvent {
	private:
		int m_repeatCount;
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_repeatCount(repeatCount) {}
		
		inline int getRepeatCount() const { return m_repeatCount;}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class NEURAL_API KeyReleasedEvent : public KeyEvent 
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class NEURAL_API KeyTypedEvent
		: public KeyEvent {
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}