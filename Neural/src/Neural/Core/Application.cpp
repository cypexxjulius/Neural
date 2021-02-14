#include "nlpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "Neural/Renderer/Renderer.h"

namespace Neural {

	Application* Application::s_instance = nullptr;

	Application::Application() 
	{
		// Checks if the application already exists
		NL_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		c_window = std::unique_ptr<Window>(Window::create());
		c_window->setEventCallback(NL_BIND_EVENT_FUNC(Application::onEvent));
	
		// Creating the ImGui Layer
		c_ImGuiLayer = new ImGuiLayer;
		pushOverlay(c_ImGuiLayer);

		c_vertexArray.reset(VertexArray::create());


		float vertices[] =
		{
			-0.5f,  -0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f,   -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,   0.5f,  0.0f, 0.8f, 0.2f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"}
		};


		vertexBuffer->setLayout(layout);
		c_vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

		c_vertexArray->setIndexBuffer(indexBuffer);

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
			in vec4 v_Color;
			
			void main()
			{		
				a_Color = v_Color;
			}

		)";

		c_shader.reset(new Shader(vertexSrc, fragmentSrc));


		// Test


		c_squareVA.reset(VertexArray::create());

		float squareVertices[] =
		{
			-0.75f,  -0.75f,  0.0f,
			 0.75f,   -0.75f, 0.0f,
			 0.75f,   0.75f,  0.0f,
			 -0.75f,   0.75f,  0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));
		squareVB->setLayout({ 
			{ShaderDataType::Float3, "a_Position" } 
		});

		c_squareVA->addVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0};
		std::shared_ptr<IndexBuffer> squareIB; 
		squareIB.reset(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		c_squareVA->setIndexBuffer(squareIB);



		char squareVertexSrc[] = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			out vec3 v_Position;
	
			void main()
			{		
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0f);
			}

		)";

		char squareFragmentSrc[] = R"(
			#version 330 core
			
			layout(location = 0) out vec4 a_Color;
			in vec3 v_Position;
			
			void main()
			{		
				a_Color = vec4(0.2, 0.3, 0.8, 1.0);
			}

		)";

		c_squareShader.reset(new Shader(squareVertexSrc, squareFragmentSrc));

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

			RenderCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1 });
			RenderCommand::clear();


			Renderer::beginScene();

			c_squareShader->bind();
			Renderer::submit(c_squareVA);

			c_shader->bind();
			Renderer::submit(c_vertexArray);

			Renderer::endScene();

			for (Layer* layer : c_LayerStack)
			{
				layer->onUpdate();
			}
			
			// ImGui Layer

			c_ImGuiLayer->begin();

			for (Layer* layer : c_LayerStack)
			{
				layer->onImGuiRender();
			}
			c_ImGuiLayer->end();


			c_window->onUpdate();

		}
	}
	
	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		c_isRunning = false;
		return true;
	}
}