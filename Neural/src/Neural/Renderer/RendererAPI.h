#pragma once

#include <glm/glm.hpp>


namespace Neural
{
	class VertexArray;

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static inline API getAPI() { return m_API; }
	private:
		static API m_API;
	};
}

