#pragma once

#include "Platform/Opengl/OpenGLContext.h"
#include "Neural/Core/Window.h"

#include <GLFW/glfw3.h>

namespace  Neural {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.s_width; }
		inline unsigned int getHeight() const override { return m_data.s_height;  }


		// Window attribute
		inline void setEventCallback(const EventCallbackFunction& callback) override { m_data.s_eventCallback= callback;  }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		inline virtual void* getNativeWindow() const
		{
			return m_window;
		}
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();


	private:
		GLFWwindow* m_window;
		struct WindowData 
		{
			const char* s_title;
			unsigned int s_width, s_height;
			bool s_vsync;
			EventCallbackFunction s_eventCallback;
		};
	private:
		WindowData m_data;
		GraphicsContext* m_context;
	};

}
