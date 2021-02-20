#pragma once

#include "Neural/Renderer/Buffer.h"
namespace Neural
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();


		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void setLayout(const BufferLayout& layout) override
		{
			m_layout = layout;
		}
		virtual const BufferLayout& getLayout() const override
		{
			return m_layout;
		}
	private:
		uint32_t m_rendererId;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();


		virtual void bind() const override;
		virtual void unbind() const override;

		
		virtual uint32_t getCount() const { return m_count; };
	private:
		uint32_t m_count;
		uint32_t m_rendererId;
	};
}

