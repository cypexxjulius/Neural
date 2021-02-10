#pragma once
namespace Neural
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1,
	};

	class Renderer
	{
	private:
		static RendererAPI c_rendererAPI;

	public:
		inline static RendererAPI getAPI() 
		{ 
			return c_rendererAPI; 
		}
	};
}
