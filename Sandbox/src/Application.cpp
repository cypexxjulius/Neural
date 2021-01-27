#include <iostream>
#include <Neural.h>

class Engine : public Neural::Application {
public:
	Engine(){}

	~Engine(){}
};

Neural::Application* Neural::CreateApplication() {
	return new Engine;
}