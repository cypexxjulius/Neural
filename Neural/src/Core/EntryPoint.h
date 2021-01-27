#pragma once

#ifdef NL_PLATFORM_WINDOWS


extern Neural::Application* Neural::CreateApplication();

int main(int argc, char** argv) {
	Neural::Logging::init();
	auto app = Neural::CreateApplication();
	NL_CORE_TRACE("Neural Engine Started");
	app->run();
	delete app;
	std::cin.get();
}


#endif // NL_PLATFORM_WINDOWS