#include "nlpch.h"
#include "Shader.h"
#include "Neural/Logging/Logging.h"

#include <glad/glad.h>
namespace Neural {
	Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
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
		c_rendererId = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(c_rendererId, vertexShader);
		glAttachShader(c_rendererId, fragmentShader);

		// Link our program
		glLinkProgram(c_rendererId);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(c_rendererId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(c_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = new char [maxLength];
			glGetProgramInfoLog(c_rendererId, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(c_rendererId);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);


			NL_CORE_FATAL("Linking the shaders failed !\n{0}", infoLog);
			NL_CORE_ASSERT(false, "");

			delete[] infoLog;
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(c_rendererId, vertexShader);
		glDetachShader(c_rendererId, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(c_rendererId);
	}

	void Shader::bind() const
	{
		glUseProgram(c_rendererId);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

}