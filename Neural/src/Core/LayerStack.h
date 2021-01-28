#pragma once

#include "Core/Core.h"
#include "Layer.h"

#include <vector>

namespace Neural
{

	class NEURAL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);

		void pushOverlay(Layer* overlay);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return c_layers.begin(); }
		std::vector<Layer*>::iterator end() { return c_layers.end(); }
	private:
		std::vector<Layer*> c_layers;
		std::vector<Layer*>::iterator c_layerInsert;
	};

}
