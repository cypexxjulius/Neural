#include "nlpch.h"
#include "LayerStack.h"

namespace Neural 
{
	LayerStack::LayerStack()
	{
		c_layerInsert = c_layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : c_layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		c_layerInsert = c_layers.emplace(c_layerInsert, layer);
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
			c_layerInsert--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(c_layers.begin(), c_layers.end(), overlay);
		if (it != c_layers.end())
			c_layers.erase(it);
	}
}