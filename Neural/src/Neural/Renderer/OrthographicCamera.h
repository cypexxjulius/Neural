#pragma once

#include <glm/glm.hpp>

namespace Neural
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		const inline glm::vec3 getPosition() const
		{
			return m_Position;
		}


		void setPosition(const glm::vec3& position) 
		{ 
			m_Position = position; 
			RecalculateViewMatrix();
		}

		float inline getRotation() const
		{
			return m_rotation;
		}

		void setRotation(float positionrot) 
		{ 
			m_rotation = positionrot; 
			RecalculateViewMatrix();
		}

		const glm::mat4 getProjectionMatrix() const
		{
			return m_ProjectMatrix;
		}

		const glm::mat4 getViewMatrix() const
		{
			return m_ViewMatrix;
		}

		const glm::mat4 getViewProjectionMatrix() const
		{
			return m_ViewProjectMatrix;
		}
	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectMatrix;


		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;
	};
}
