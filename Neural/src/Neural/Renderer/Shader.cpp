#include "nlpch.h"
#include "Shader.h"
#include "Neural/Logging/Logging.h"
#include "Neural/Renderer/Renderer.h"

#include "Platform/Opengl/OpenGLShader.h"

namespace Neural {
	Shader* Shader::create(const char* vertexSrc, const char* fragmentSrc)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: 
			{
				NL_ASSERT(false, "RendererAPI is currently not supported!"); 
				break;
			}
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		NL_ASSERT(false, "Unknown RendererAPI !");
		return nullptr;
	}
}