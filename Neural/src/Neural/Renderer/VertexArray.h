#pragma once
namespace Neural
{
	class VertexBuffer;
	class IndexBuffer;

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void setIndexBuffer(IndexBuffer* indexBuffer) = 0;

		virtual const std::vector<VertexBuffer*> getVertexBuffers() const = 0;
		virtual const IndexBuffer* getIndexBuffer() const = 0;

		static VertexArray* create();
	};
}
