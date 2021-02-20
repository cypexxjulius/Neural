#pragma once
#include "Event.h"

namespace Neural 
{
	class NEURAL_API MouseMovedEvent : public Event
	{
	private:
		float m_mouseX, m_mouseY;
	public:
		MouseMovedEvent(float x, float y)
			: m_mouseX(x), m_mouseY(y) {}

		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }
		
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NEURAL_API MouseScrolledEvent : public Event
	{
	private:
		float m_xOffset, m_yOffset;
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float getXOffset() const { return m_xOffset; }
		inline float getYOffset() const { return m_yOffset; }

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class NEURAL_API MouseButtonEvent : public Event {
	protected:
		int m_button;
		MouseButtonEvent(int button)
			: m_button(button) {}
	public:
		inline int getMouseButton() const { return m_button; }
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