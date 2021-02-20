#pragma once
namespace Neural
{
	enum class ShaderDataType
	{
		None = 0, 
		Float, Float2, Float3, Float4, 
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t shaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:  return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;

			case ShaderDataType::Mat3: return 4 * 4 * 4;
			case ShaderDataType::Mat4: return 4 * 4 * 4 * 4;

			case ShaderDataType::Int:  return 4;
			case ShaderDataType::Int2: return 4 * 2;
			case ShaderDataType::Int3: return 4 * 3;
			case ShaderDataType::Int4: return 4 * 4;

			case ShaderDataType::Bool: return 1;
		}
		NL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		const char* s_name;
		ShaderDataType s_type;
		uint32_t s_offset;
		uint32_t s_size;
		bool s_normalized;

		BufferElement()
			: s_name(nullptr), s_type(ShaderDataType::None), s_offset(0), s_size(0), s_normalized(0)
		{}
		
		BufferElement(ShaderDataType type, const char *name, bool normalized = 0)
			: s_name(name), s_type(type), s_size(shaderDataTypeSize(type)), s_offset(0), s_normalized(normalized)
		{}

		uint32_t getComponentCount() const
		{
			switch (s_type)
			{
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;

			case ShaderDataType::Mat3: return 4 * 4 * 4;
			case ShaderDataType::Mat4: return 4 * 4 * 4 * 4;

			case ShaderDataType::Int:  return 1;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Int4: return 4;

			case ShaderDataType::Bool: return 1;
			}
			NL_CORE_ASSERT(false, "Component Count Failed!");
			return 0;
		}
	};

	/*
	Buffer Layout
	*/
	
	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_elements(elements) 
		{
			calculateOffsetsAndStride();
		}
		inline const std::vector<BufferElement>& getElements() const { return m_elements;  }
		
		inline uint32_t getStride() const { return m_stride; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	private:
		void calculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_elements)
			{
				element.s_offset = offset;
				offset += element.s_size;
				m_stride += element.s_size;
			}
		}
	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};


	/*
	Vertex Buffer
	*/


	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& getLayout() const = 0;

		static VertexBuffer* create(float * vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}


		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static IndexBuffer* create(uint32_t* vertices, uint32_t size);
	};
}

