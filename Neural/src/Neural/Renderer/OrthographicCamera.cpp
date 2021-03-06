#include "nlpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Neural
{
	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
		: m_ProjectMatrix(glm::ortho(left, right, top, bottom)), m_ViewMatrix(1)
	{
		m_width =  ((left < 0) ? 0 - left : left) + (( right < 0) ? 0 - right : right);
		m_height = ((top < 0) ? 0 - top : top)    + ((bottom < 0) ? 0 - bottom : bottom);
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
		
		m_ViewMatrix = glm::inverse(transform);
		
		m_ViewProjectMatrix = m_ProjectMatrix * m_ViewMatrix;

	}

}