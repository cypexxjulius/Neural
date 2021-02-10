#pragma once

#include "nlpch.h"

#include "Neural/Core/Core.h"
#include "Neural/Events/Event.h"


namespace Neural {
	struct WindowProps
	{
		const char* s_title;
		unsigned int s_width;
		unsigned int s_height;

		WindowProps(const char *title = "Neural Engine", 
					unsigned int width = 1280,
					unsigned int height = 720)
			: s_title(title), s_width(width), s_height(height)
		{
		}
	};

	class Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;
		virtual ~Window(){}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes 
		virtual void setEventCallback(const EventCallbackFunction&) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
	};

}
