#pragma once
namespace Neural
{
	class Shader
	{
	public:
		Shader(const char* vertexSrc, const char* fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;

	private:
		unsigned int c_rendererId;
	};

}
