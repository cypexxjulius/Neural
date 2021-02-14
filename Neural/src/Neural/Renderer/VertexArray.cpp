#include "nlpch.h"
#include "VertexArray.h"
#include "Platform/Opengl/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Neural
{
	VertexArray* VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			{
				NL_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();

		}
		NL_ASSERT(false, "Unknown RendererAPI");
		return 0;
	}
}