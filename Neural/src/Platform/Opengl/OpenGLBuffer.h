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
			c_layout = layout;
		}
		virtual const BufferLayout& getLayout() const override
		{
			return c_layout;
		}
	private:
		uint32_t c_rendererId;
		BufferLayout c_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();


		virtual void bind() const override;
		virtual void unbind() const override;

		
		virtual uint32_t getCount() const { return c_count; };
	private:
		uint32_t c_count;
		uint32_t c_rendererId;
	};
}

