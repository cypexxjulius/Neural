#include "nlpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Neural {

	Application* Application::s_instance = nullptr;

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

		float vertices[3 * 3] =
		{
			-0.5f,  -0.5f,  0.0f,
			 0.5f,   -0.5f, 0.0f,
			 0.0f,   0.5f,  0.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };

		c_vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		c_indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));


		char* vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			
			out vec3 v_position;		
	
			void main()
			{		
				v_position = a_position;
				gl_Position = vec4(a_position, 1.0f);
			}

		)";

		char* fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_position;
			
			void main()
			{		
				color = vec4(v_position * 0.5 + 0.5, 1.0f);
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