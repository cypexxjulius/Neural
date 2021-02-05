#pragma once
#include "Event.h"

namespace Neural 
{
	class NEURAL_API MouseMovedEvent : public Event
	{
	private:
		float c_mouseX, c_mouseY;
	public:
		MouseMovedEvent(float x, float y)
			: c_mouseX(x), c_mouseY(y) {}

		inline float getX() const { return c_mouseX; }
		inline float getY() const { return c_mouseY; }
		
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NEURAL_API MouseScrolledEvent : public Event
	{
	private:
		float c_xOffset, c_yOffset;
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: c_xOffset(xOffset), c_yOffset(yOffset) {}

		inline float getXOffset() const { return c_xOffset; }
		inline float getYOffset() const { return c_yOffset; }

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NEURAL_API MouseButtonEvent : public Event {
	protected:
		int c_button;
		MouseButtonEvent(int button)
			: c_button(button) {}
	public:
		inline int getMouseButton() const { return c_button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NEURAL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
	class NEURAL_API MouseButtonReleasedEvent: public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}