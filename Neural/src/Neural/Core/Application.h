#pragma once

#include "Core.h"
#include "Window.h"
#include "Neural/Core/LayerStack.h"

// Events 
#include "Neural/Events/Event.h"
#include "Neural/Events/ApplicationEvent.h"

// ImGui
#include "Neural/ImGui/ImGuiLayer.h"

// Rendering
#include "Neural/Renderer/Shader.h"
#include "Neural/Renderer/Buffer.h"
#include "Neural/Renderer/VertexArray.h"


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
		inline Window& getWindow() { return *c_window; };
	private:
		bool onWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> c_window;
		ImGuiLayer* c_ImGuiLayer;

		bool c_isRunning = true;
		LayerStack c_LayerStack;
	private:
		static Application* s_instance;

		std::shared_ptr<Shader> c_shader;
		std::shared_ptr<VertexArray> c_vertexArray;

		std::shared_ptr<Shader> c_squareShader;
		std::shared_ptr<VertexArray> c_squareVA;
	};
	
	Application* CreateApplication();
}