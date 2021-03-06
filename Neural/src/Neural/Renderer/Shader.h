#pragma once

#include <glm/glm.hpp>

namespace Neural
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void uploadUniformInt(const char* name, int value) const = 0;
		virtual void uploadUniformFloat(const char* name, float value) const = 0;
		virtual void uploadUniformFloat2(const char* name, const glm::vec2& values) const = 0;
		virtual void uploadUniformFloat3(const char* name, const glm::vec3& values) const = 0;
		virtual void uploadUniformFloat4(const char* name, const glm::vec4& values) const = 0;

		virtual void uploadUniformMat3(const char* name, const glm::mat3& matrix) const = 0;
		virtual void uploadUniformMat4(const char* name, const glm::mat4& values) const = 0;

		static Shader* create(const char* vertexSrc, const char* fragmentSrc);
	};

}
