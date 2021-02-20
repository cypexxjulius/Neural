#include "nlpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
 
#include <GLFW/glfw3.h>

namespace Neural 
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		NL_ASSERT(windowHandle, "Window handle is not valid!");
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NL_CORE_ASSERT(status, "Failed to initialize Glad!");
		

		// Printing system information
		NL_CORE_INFO("OpenGL Info");
		NL_CORE_INFO("	Vendor:		{0}", glGetString(GL_VENDOR));
		NL_CORE_INFO("	Renderer:	{0}", glGetString(GL_RENDERER));
		NL_CORE_INFO("	Version:	{0}", glGetString(GL_VERSION));
	}	
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}