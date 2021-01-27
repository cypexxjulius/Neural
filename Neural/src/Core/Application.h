#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Neural {
	class NEURAL_API Application {
	public:
		Application();

		void run();

		virtual ~Application();

		void onEvent(Event& event);
	private:
		bool onWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> c_window;
		bool c_isRunning = true;
	};
	
	Application* CreateApplication();
}