#include "nlpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/Opengl/OpenGLBuffer.h"

namespace Neural 
{
	IndexBuffer* IndexBuffer::create(uint32_t* vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None :
			{
				NL_ASSERT(false, "RendererAPI::None is not supported");
				return NULL;
			}		
			case RendererAPI::API::OpenGL :
				return new OpenGLIndexBuffer(vertices, size);
				
		}
		NL_ASSERT(false, "Unknown RendererAPI");
		return NULL;
	}
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
		{
			NL_ASSERT(false, "RendererAPI::None is not supported");
			return NULL;
		}
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);

		}
		NL_ASSERT(false, "Unknown RendererAPI");
		return NULL;
	}
}