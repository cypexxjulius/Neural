#include "nlpch.h"
#include "OpenGLShader.h"


#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Neural
{
	OpenGLShader::OpenGLShader(const char* vertexSrc, const char* fragmentSrc)
		: m_rendererID(0)
	{

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = (const GLchar*)vertexSrc;
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = new char[maxLength];
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			NL_CORE_FATAL("Vertex shader compilation failed !\n{0}", infoLog);
			NL_CORE_ASSERT(false, "");

			delete[] infoLog;
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		source = (const GLchar*)fragmentSrc;
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = new char[maxLength];
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);


			NL_CORE_FATAL("Fragment shader compilation failed !\n{0}", infoLog);
			NL_CORE_ASSERT(false, "");

			delete[] infoLog;
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_rendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_rendererID, vertexShader);
		glAttachShader(m_rendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_rendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_rendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = new char[maxLength];
			glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_rendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);


			NL_CORE_FATAL("Linking the shaders failed !\n{0}", infoLog);
			NL_CORE_ASSERT(false, "");

			delete[] infoLog;
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_rendererID, vertexShader);
		glDetachShader(m_rendererID, fragmentShader);
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_rendererID);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_rendererID);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

	int inline OpenGLShader::getUniformLocation(const char* name) const 
	{
		return glGetUniformLocation(m_rendererID, name);
	}

	void OpenGLShader::uploadUniformInt(const char* name, int value) const
	{
		int location = getUniformLocation(name);
		glUniform1i(location, value);
	}

	void OpenGLShader::uploadUniformFloat(const char* name, float value) const
	{
		int location = getUniformLocation(name);
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadUniformFloat2(const char* name, const glm::vec2& values) const
	{
		int location = getUniformLocation(name);
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::uploadUniformFloat3(const char* name, const glm::vec3& values) const
	{
		int location = getUniformLocation(name);
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::uploadUniformFloat4(const char* name, const glm::vec4& values) const
	{
		int location = getUniformLocation(name);
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::uploadUniformMat3(const char* name, const glm::mat3& matrix) const
	{
		int location = getUniformLocation(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformMat4(const char* name, const glm::mat4& matrix) const
	{
		int location = getUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}