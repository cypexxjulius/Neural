#pragma once

#include "RendererAPI.h"

#include "RendererAPI.h"

namespace Neural
{
	class RenderCommand
	{
	public:
		inline static void setClearColor(const glm::vec4& color)
		{
			c_rendererAPI->setClearColor(color);
		}
		inline static void clear()
		{
			c_rendererAPI->clear();
		}

		inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			c_rendererAPI->drawIndexed(vertexArray);
		}

	private:
		static RendererAPI* c_rendererAPI;
	};
}