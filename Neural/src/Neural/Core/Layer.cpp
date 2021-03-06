#include "nlpch.h"
#include "Layer.h"

#include "Neural/Core/Timestep.h"

namespace Neural 
{
	Layer::Layer(const char* debugName)
		: m_debugName(debugName) {}

	Layer::~Layer() {}
	
	void Layer::onAttach() {}
	void Layer::onDetach() {}
	void Layer::onUpdate(Timestep timestep) {}
	void Layer::onEvent(Event& event) {}
	void Layer::onImGuiRender(Timestep timestep) {}
}