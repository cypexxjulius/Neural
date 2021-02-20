#pragma once

#include <glm/glm.hpp>

namespace Neural
{
	class Shader
	{
	public:
		Shader(const char* vertexSrc, const char* fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;

		void uploadUniformMat4(const char* name, const glm::mat4& matrix);



	private:
		unsigned int m_rendererID;
	};

}
