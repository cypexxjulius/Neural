#include "nlpch.h"
#include "WindowsWindow.h"

#include "Neural/Events/ApplicationEvent.h"
#include "Neural/Events/MouseEvent.h"
#include "Neural/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Neural 
{
	static bool i_GLFWInitialized = false;

	static void errorCallback(int error, const char *description) 
	{
		NL_CORE_ERROR("GLFW Error {0}\n{1}", error, description);
	}

	Window* Window::create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		this->init(props);
	}

	WindowsWindow::~WindowsWindow() 
	{
		this->shutdown();
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		m_data.s_title = props.s_title;
		m_data.s_width = props.s_width;
		m_data.s_height = props.s_height;


		NL_CORE_INFO("Creating window {0} ({1}, {2})", props.s_title, props.s_width, props.s_height);
		if(!i_GLFWInitialized)
		{
			int success = glfwInit();
			NL_CORE_ASSERT(success, "Failed to initialize GLFW");

			glfwSetErrorCallback(errorCallback);

			i_GLFWInitialized = true;
		}
		m_window = glfwCreateWindow((int)props.s_width, (int)props.s_height, props.s_title, nullptr, nullptr);
		
		m_context = new OpenGLContext(m_window);
		m_context->init();
	

		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);


		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.s_width = width;
				data.s_height = height;
				
				glViewport(0, 0, width, height);
				
				
				WindowResizeEvent event(width, height);
				data.s_eventCallback(event);
				
		});
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.s_eventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch(action) 
				{
					case GLFW_PRESS: 
					{
						KeyPressedEvent event(key, 0);
						data.s_eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.s_eventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.s_eventCallback(event);
						break;
					}
				}
		});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.s_eventCallback(event);

		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
				switch (action)
				{
					case GLFW_PRESS : 
					{
						MouseButtonPressedEvent event(button);
						data.s_eventCallback(event);
						break;
					}
					case GLFW_RELEASE : 
					{
						MouseButtonReleasedEvent event(button);
						data.s_eventCallback(event);
						break;
					}
				}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.s_eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) 
		{

			static float xoldPos, yoldPos= 0;
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos, (float)xPos - xoldPos, (float)yPos - yoldPos);
			
			xoldPos = (float)xPos;
			yoldPos = (float)yPos;
			data.s_eventCallback(event);
		});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}
	void WindowsWindow:: onUpdate() 
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}

	void WindowsWindow::setVSync(bool enabled) {
		glfwSwapInterval(enabled ? 1 : 0);
		m_data.s_vsync = enabled;
	}

	bool WindowsWindow::isVSync() const
	{
		return m_data.s_vsync;
	}
}