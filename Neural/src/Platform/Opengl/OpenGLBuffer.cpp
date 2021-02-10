#include "nlpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Neural
{

	/*
	Vertex Buffer
	*/

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &c_rendererId);
		glBindBuffer(GL_ARRAY_BUFFER, c_rendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &c_rendererId);
	}

	void OpenGLVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, c_rendererId);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	/*
	Index Buffer
	*/
	
	
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: c_count(count)
	{
		glCreateBuffers(1, &c_rendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_rendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &c_rendererId);
	}
	void OpenGLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_rendererId);
	}
	void OpenGLIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
