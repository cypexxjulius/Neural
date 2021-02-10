#pragma once

#include "Core.h"
#include "Window.h"
#include "Neural/Core/LayerStack.h"
#include "Neural/Events/Event.h"
#include "Neural/Events/ApplicationEvent.h"
#include "Neural/ImGui/ImGuiLayer.h"
#include "Neural/Renderer/Shader.h"
#include "Neural/Renderer/Buffer.h"

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


		unsigned int c_vertexArray;
		std::unique_ptr<Shader> c_shader;
		std::unique_ptr<VertexBuffer> c_vertexBuffer;
		std::unique_ptr<IndexBuffer> c_indexBuffer;
	};
	
	Application* CreateApplication();
}