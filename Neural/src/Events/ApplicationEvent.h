#pragma once


#include "Event.h"

#include <sstream>
namespace Neural {
	class NEURAL_API WindowResizeEvent
		: public Event {
	private:
		unsigned int c_width, c_height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: c_width(width), c_height(height) {}

		inline unsigned int getWidth() const {
			return c_width;
		}
		inline unsigned int getHeight() const {
			return c_height;
		}

		EVENT_CLASS_TYPE(WindowResize)
		
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class NEURAL_API WindowCloseEvent : public Event 
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class NEURAL_API AppTickEvent : public Event 
	{
	public:
		AppTickEvent() {}


		EVENT_CLASS_TYPE(AppTick)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class NEURAL_API AppRendererEvent
		: public Event {
	public:
		void AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}