#pragma once

#include "Neural/Renderer/VertexArray.h"

class VertexBuffer;
class IndexBuffer;

namespace Neural 
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() {}

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(VertexBuffer* vertexBuffer) override;
		virtual void setIndexBuffer(IndexBuffer* indexBuffer) override;
		
		virtual const std::vector<VertexBuffer*> getVertexBuffers() const override
		{
			return m_vertexBuffer;
		}
		virtual const IndexBuffer* getIndexBuffer() const override
		{
			return m_indexBuffer;
		}
	private:
		uint32_t m_rendererId;
		std::vector<VertexBuffer*> m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
	};
}

