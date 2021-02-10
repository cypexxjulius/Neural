#include "nlpch.h"
#include "Layer.h"


namespace Neural 
{
	Layer::Layer(const char* debugName)
		: c_debugName(debugName) {}

	Layer::~Layer() {}
	
	void Layer::onAttach() {}
	void Layer::onDetach() {}
	void Layer::onUpdate() {}
	void Layer::onEvent(Event& event) {}
	void Layer::onImGuiRender() {}
}