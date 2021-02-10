#include "nlpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace Neural 
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: c_windowHandle(windowHandle)
	{
		NL_ASSERT(windowHandle, "Window handle is not valid!");
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(c_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NL_CORE_ASSERT(status, "Failed to initialize Glad!");
	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(c_windowHandle);
	}
}