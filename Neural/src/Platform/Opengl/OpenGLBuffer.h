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
	private:
		uint32_t c_rendererId;
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

