#pragma once

#ifdef NL_PLATFORM_WINDOWS


extern Neural::Application* Neural::CreateApplication();

int main(int argc, char** argv) {
	auto app = Neural::CreateApplication();
	app->run();
	delete app;
}


#endif // NL_PLATFORM_WINDOWS