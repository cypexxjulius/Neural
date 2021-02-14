#include "nlpch.h"
#include "RenderCommand.h"

#include "Platform/Opengl/OpenGLRendererAPI.h"

namespace Neural 
{
	RendererAPI* RenderCommand::c_rendererAPI = new OpenGLRendererAPI;
}