#pragma once

#include "Core.h"

namespace Neural {
	class NEURAL_API Application {
	public:
		Application();

		void run();

		virtual ~Application();
	};
	
	Application* CreateApplication();
}