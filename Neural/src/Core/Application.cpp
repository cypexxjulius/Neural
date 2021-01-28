#include "nlpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Neural {

#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() 
	{
		c_window = std::unique_ptr<Window>(Window::create());
		c_window->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));
	}
	Application::~Application() {

	}
	void Application::pushLayer(Layer *layer)
	{
		c_LayerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		c_LayerStack.pushOverlay(overlay);
	}

	void Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));
		NL_CORE_TRACE("{0}", event);

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