#pragma once

#include "Neural/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Neural
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vertexSrc, const char* fragmentSrc);
		~OpenGLShader();

		void bind() const;
		void unbind() const;

		virtual void uploadUniformInt(const char* name, int value) const override;
		virtual void uploadUniformFloat(const char* name, float value) const override;
		virtual void uploadUniformFloat2(const char* name, const glm::vec2& values) const override;
		virtual void uploadUniformFloat3(const char* name, const glm::vec3& values) const override;
		virtual void uploadUniformFloat4(const char* name, const glm::vec4& values) const override;

		virtual void uploadUniformMat3(const char* name, const glm::mat3& matrix) const override;
		virtual void uploadUniformMat4(const char* name, const glm::mat4& values) const override;
	private:
		int inline getUniformLocation(const char *name) const;
	private:
		unsigned int m_rendererID;
	};

}


