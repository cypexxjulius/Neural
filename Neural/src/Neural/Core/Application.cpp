#include "nlpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "Neural/Renderer/Renderer.h"

#include <imgui.h>

namespace Neural {

	Application* Application::s_instance = nullptr;

	Application::Application() 
	{
		// Checks if the application already exists
		NL_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(NL_BIND_EVENT_FUNC(Application::onEvent));
			
		// Creating the ImGui Layer
		m_ImGuiLayer = new ImGuiLayer;
		pushOverlay(m_ImGuiLayer);
	}

	Application::~Application() 
	{

	}

	void Application::pushLayer(Layer *layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_LayerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(NL_BIND_EVENT_FUNC(Application::onWindowClose));

		for (auto i = m_LayerStack.end(); i != m_LayerStack.begin();)
		{
			(*--i)->onEvent(event);
			if (event.m_handled)
				break;
		}
	}

	void Application::run()
	{
		while (m_isRunning) 
		{

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_lastFrameTime;
			m_lastFrameTime = time;

			
			for (Layer* layer : m_LayerStack)
			{
				layer->onUpdate(timestep);
			}
			
			// ImGui Layer

			m_ImGuiLayer->begin();

			for (Layer* layer : m_LayerStack)
				layer->onImGuiRender();
			
			m_ImGuiLayer->end();

			m_window->onUpdate();

		}
	}
	
	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		m_isRunning = false;
		return true;
	}
}