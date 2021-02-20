#include "nlpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Neural
{
	static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:  return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;

		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;

		case ShaderDataType::Int:  return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;

		case ShaderDataType::Bool: return GL_BOOL;
		}

		NL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_rendererId);
	}
	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_rendererId);
	}
	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		NL_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_rendererId);
		vertexBuffer->bind();


		uint32_t index = 0;
		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.getComponentCount(),
				shaderDataTypeToOpenGLBaseType(element.s_type),
				element.s_normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.s_offset);
			index++;
		}

		m_vertexBuffer.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_rendererId);
		indexBuffer->bind();

		m_indexBuffer = indexBuffer;
	}
}