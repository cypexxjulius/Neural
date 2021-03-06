#include "nlpch.h"
#include "Timestep.h"

#include <glfw/glfw3.h>

namespace Neural
{
	float Timestep::getTime()
	{
		return (float)glfwGetTime();
	}
}