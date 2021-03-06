#pragma once

#include "Neural/Renderer/RendererAPI.h"

namespace Neural
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void setClearColor(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override;

	};
}

