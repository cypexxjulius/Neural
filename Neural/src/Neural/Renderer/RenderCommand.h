#pragma once

#include "RendererAPI.h"


namespace Neural
{	
	class RenderCommand
	{
	public:
		inline static void setClearColor(const glm::vec4& color)
		{
			m_rendererAPI->setClearColor(color);
		}
		inline static void clear()
		{
			m_rendererAPI->clear();
		}

		inline static void drawIndexed(const VertexArray* vertexArray)
		{
			m_rendererAPI->drawIndexed(vertexArray);
		}

	private:
		static RendererAPI* m_rendererAPI;
	};
}