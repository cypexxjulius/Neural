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
		inline int GetKeyCode() const {
			return c_keyCode;
		}
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode)
			: c_keyCode(keycode) {}

		int c_keyCode;
	};

	class NEURAL_API KeyPressedEvent
		: public KeyEvent {
	private:
		int c_repeatCount;
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), c_repeatCount(repeatCount) {}
		
		inline int getRepeatCount() const { return c_repeatCount;}

		EVENT_CLASS_TYPE(KeyPressed)
	};
	class NEURAL_API KeyReleasedEvent : public KeyEvent 
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}