#include "nlpch.h"
#include "Renderer.h"


namespace Neural
{
	void Renderer::beginScene(OrthographicCamera& camera)
	{

	}
	void Renderer::endScene()
	{
	}
	void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}