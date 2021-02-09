#include <Neural.h>

class ExampleLayer : public Neural::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void onUpdate() override
	{
		if (Neural::Input::isKeyPressed(NL_KEY_TAB))
			NL_INFO("Tab Pressed");
	}
	void onEvent(Neural::Event& event) override
	{
	}

};



class Engine : public Neural::Application {
public:
	Engine()
	{
	}

	~Engine(){}
};

Neural::Application* Neural::CreateApplication() {
	return new Engine;
}