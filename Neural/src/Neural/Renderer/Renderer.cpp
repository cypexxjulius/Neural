#include "nlpch.h"

#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Renderer.h"

namespace Neural
{

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::beginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjMatrix = camera.getViewProjectionMatrix();
	}
	void Renderer::endScene()
	{
	}
	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->bind();

		shader->uploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjMatrix);
		shader->uploadUniformMat4("u_Transform", transform);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}