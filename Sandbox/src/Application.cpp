#include <Neural.h>

class ExampleLayer : public Neural::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void onUpdate() override
	{
		NL_INFO("ExampleLayer::Update");
	}
	void onEvent(Neural::Event& event) override
	{
		NL_TRACE("{0}", event);
	}

};



class Engine : public Neural::Application {
public:
	Engine()
	{
		pushLayer(new ExampleLayer());
	}

	~Engine(){}
};

Neural::Application* Neural::CreateApplication() {
	return new Engine;
}