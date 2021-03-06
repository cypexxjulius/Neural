#pragma once
#include "Event.h"
#include <glm/glm.hpp>

namespace Neural 
{
	class NEURAL_API MouseMovedEvent : public Event
	{
	private:
		glm::vec2 m_pos;
		glm::vec2 m_delta;
	public:
		MouseMovedEvent(float x, float y, float xdelta, float ydelta)
			: m_pos(x, y), m_delta(xdelta, ydelta) {}

		inline glm::vec2 getPosition() const { return m_pos; }
		inline glm::vec2 getDelta() const { return m_delta; }
		
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