#pragma once

#include "Core.h"
#include "Window.h"
#include "Neural/Core/LayerStack.h"

// Events 
#include "Neural/Events/Event.h"
#include "Neural/Events/ApplicationEvent.h"

// Input Polling
#include "Neural/Core/Input.h"

// Timing

#include "Neural/Core/Timestep.h"


// ImGui
#include "Neural/ImGui/ImGuiLayer.h"

// Rendering
#include "Neural/Renderer/Shader.h"
#include "Neural/Renderer/Buffer.h"
#include "Neural/Renderer/VertexArray.h"
#include "Neural/Renderer/OrthographicCamera.h"

namespace Neural {
	class Application {
	public:
		Application();

		void run();

		virtual ~Application();

		void onEvent(Event& event);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		inline static Application& get() { return *s_instance; };
		inline Window& getWindow() { return *m_window; };
	private:
		bool onWindowClose(WindowCloseEvent& event);

	private:
		Scope<Window> m_window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_isRunning = true;
		LayerStack m_LayerStack;
		float m_lastFrameTime = 0.0f;
	private:
		
		static Application* s_instance;
	};
	
	Application* CreateApplication();
}