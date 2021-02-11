#include "nlpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Neural {

	Application* Application::s_instance = nullptr;

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

	Application::Application() 
	{
		// Checks if the application already exists
		NL_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		c_window = std::unique_ptr<Window>(Window::create());
		c_window->setEventCallback(NL_BIND_EVENT_FUNC(Application::onEvent));
	
		c_ImGuiLayer = new ImGuiLayer;

		pushOverlay(c_ImGuiLayer);

		// Vertex Array

		glGenVertexArrays(1, &c_vertexArray);
		glBindVertexArray(c_vertexArray);


		// Vertex Buffer 
		

		
		// Index Buffer 

		float vertices[3 * 7] =
		{
			-0.5f,  -0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f,   -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,   0.5f,  0.0f, 0.8f, 0.2f, 0.2f, 1.0f
		};


		c_vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		
		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float4, "a_Color"}
			};

			c_vertexBuffer->setLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = c_vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(	index, 
									element.getComponentCount(), 
									shaderDataTypeToOpenGLBaseType(element.s_type),
									element.s_normalized ? GL_TRUE : GL_FALSE, 
									layout.getStride(), 
									(const void *)element.s_offset);
			index++;
		}


		uint32_t indices[3] = { 0, 1, 2 };
		c_indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));


		char vertexSrc[] = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec3 v_Position;		
			out vec4 v_Color;
	
			void main()
			{		
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0f);
			}

		)";

		char fragmentSrc[] = R"(
			#version 330 core
			
			layout(location = 0) out vec4 a_Color;
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{		
				a_Color = v_Color;
			}

		)";

		c_shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application() {

	}
	void Application::pushLayer(Layer *layer)
	{
		c_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		c_LayerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(NL_BIND_EVENT_FUNC(Application::onWindowClose));

		for (auto i = c_LayerStack.end(); i != c_LayerStack.begin();)
		{
			(*--i)->onEvent(event);
			if (event.c_handled)
				break;
		}
	}

	void Application::run()
	{
		while (c_isRunning) {
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			c_shader->bind();
			glBindVertexArray(c_vertexArray);
			glDrawElements(GL_TRIANGLES, c_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : c_LayerStack)
				layer->onUpdate();

			c_ImGuiLayer->begin();

			for (Layer* layer : c_LayerStack)
				layer->onImGuiRender();

			c_ImGuiLayer->end();


			c_window->onUpdate();

			GLenum errorCode;
			while ((errorCode = glGetError()) != GL_NO_ERROR)
				NL_CORE_ERROR("OPenGL Error: {0}", errorCode);
		}
	}
	
	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		c_isRunning = false;
		return true;
	}
}