#include "nlpch.h"
#include "Neural/Core/LayerStack.h"

namespace Neural 
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : c_layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		c_layers.emplace(c_layers.begin() + c_layerInsertIndex, layer);
		c_layerInsertIndex++;
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		c_layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(c_layers.begin(), c_layers.end(), layer);
		if(it != c_layers.end())
		{
			c_layers.erase(it);
			c_layerInsertIndex--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(c_layers.begin(), c_layers.end(), overlay);
		if (it != c_layers.end())
			c_layers.erase(it);
	}
}