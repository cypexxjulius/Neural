#pragma once

#include "Neural/Renderer/VertexArray.h"

namespace Neural 
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() {}

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override
		{
			return c_vertexBuffer;
		}
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override
		{
			return c_indexBuffer;
		}
	private:
		uint32_t c_rendererId;
		std::vector<std::shared_ptr<VertexBuffer>> c_vertexBuffer;
		std::shared_ptr<IndexBuffer> c_indexBuffer;
	};
}

