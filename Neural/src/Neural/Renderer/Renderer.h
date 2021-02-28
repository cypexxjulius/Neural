#pragma once


#include "RenderCommand.h"



namespace Neural
{
	class Shader;
	class OrthographicCamera;


	class Renderer
	{
	public:

		static void beginScene(OrthographicCamera& camera); 

		static void endScene();

		static void submit(const Shader* shader, const VertexArray* vertexArray);

		inline static RendererAPI::API getAPI() 
		{ 
			return RendererAPI::getAPI(); 
		}
	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};
		static SceneData* m_SceneData;
	};
}
