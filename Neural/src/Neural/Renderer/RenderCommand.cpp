#include "nlpch.h"
#include "RenderCommand.h"

#include "Platform/Opengl/OpenGLRendererAPI.h"

namespace Neural 
{
	RendererAPI* RenderCommand::m_rendererAPI = new OpenGLRendererAPI;
}