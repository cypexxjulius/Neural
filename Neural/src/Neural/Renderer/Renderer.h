#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"

namespace Neural
{
	class Renderer
	{
	public:

		static void beginScene(OrthographicCamera& camera); 

		static void endScene();

		static void submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API getAPI() 
		{ 
			return RendererAPI::getAPI(); 
		}
	};
}
