#pragma once

#include "Neural/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Neural
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override; 
	private:
		GLFWwindow* c_windowHandle;
	};
}
