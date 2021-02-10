#pragma once

extern Neural::Application* Neural::CreateApplication();

int main(int argc, char** argv) {
	// Initialize logging system
	Neural::Logging::init();

	// Initializing application
	auto app = Neural::CreateApplication();
	NL_CORE_TRACE("Neural Engine Started");

	// Start game loop
	app->run();
	
	delete app;

	std::cin.get();
}
