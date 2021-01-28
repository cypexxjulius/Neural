#pragma once

#include "Core.h"
#include "Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Neural {
	class NEURAL_API Application {
	public:
		Application();

		void run();

		virtual ~Application();

		void onEvent(Event& event);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

	private:
		bool onWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> c_window;
		bool c_isRunning = true;
		LayerStack c_LayerStack;
	};
	
	Application* CreateApplication();
}