#include "nlpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Neural {

	Application* Application::s_instance = nullptr;

	Application::Application() 
	{
		NL_ASSERT(!s_instance, "Application Created a second time");
		c_window = std::unique_ptr<Window>(Window::create());
		c_window->setEventCallback(NL_BIND_EVENT_FUNC(Application::onEvent));
		s_instance = this;
	}
	Application::~Application() {

	}
	void Application::pushLayer(Layer *layer)
	{
		c_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		c_LayerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(NL_BIND_EVENT_FUNC(Application::onWindowClose));

		for (auto i = c_LayerStack.end(); i != c_LayerStack.begin();)
		{
			(*--i)->onEvent(event);
			if (event.c_handled)
				break;
		}
	}

	void Application::run()
	{
		while (c_isRunning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : c_LayerStack)
				layer->onUpdate();

			c_window->onUpdate();
		}
	}
	
	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		c_isRunning = false;
		return true;
	}
}