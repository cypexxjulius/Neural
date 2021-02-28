#include "nlpch.h"

#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Renderer.h"

namespace Neural
{

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::beginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjMatrix = camera.getViewProjectionMatrix();
	}
	void Renderer::endScene()
	{
	}
	void Renderer::submit(const Shader* shader, const VertexArray* vertexArray)
	{
		shader->bind();

		shader->uploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjMatrix);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}