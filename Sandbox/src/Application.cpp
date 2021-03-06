#include <Neural.h>
#include <imgui.h>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Neural::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), 
		m_CameraPosition(0.0f, 0.0f, 0.0f), 
		m_color(0.0f, 0.3f, 0.5f), m_deltaPos(0.0f),
		m_xMultiplier(m_Camera.getHeight() / Neural::Application::get().getWindow().getHeight()),
		m_yMultiplier(m_Camera.getWidth()  / Neural::Application::get().getWindow().getWidth())
	{

		m_vertexArray.reset(Neural::VertexArray::create());


		float vertices[] =
		{
			-0.5f,  -0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f,  -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,   0.5f,  0.0f, 0.8f, 0.2f, 0.2f, 1.0f
		};

		Neural::Ref<Neural::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Neural::VertexBuffer::create(vertices, sizeof(vertices)));

		Neural::BufferLayout layout = {
			{ Neural::ShaderDataType::Float3, "a_Position" },
			{ Neural::ShaderDataType::Float4, "a_Color"    }
		};


		vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Neural::Ref<Neural::IndexBuffer> indexBuffer; 
		indexBuffer.reset(Neural::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_vertexArray->setIndexBuffer(indexBuffer);

		char vertexSrc[] = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;		
			out vec4 v_Color;
	
			void main()
			{		
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
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

		m_shader.reset(Neural::Shader::create(vertexSrc, fragmentSrc));


		// Test


		m_squareVA.reset(Neural::VertexArray::create());

		float squareVertices[] =
		{
			-0.5f,  -0.5f,  
			 0.5f,  -0.5f,
			 0.5f,   0.5f, 
			-0.5f,   0.5f
		};

		Neural::Ref<Neural::VertexBuffer> squareVB; 
		squareVB.reset(Neural::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
		
		squareVB->setLayout({
			{ Neural::ShaderDataType::Float2, "a_Position" }
		});

		m_squareVA->addVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		Neural::Ref<Neural::IndexBuffer> squareIB; 
		squareIB.reset(Neural::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_squareVA->setIndexBuffer(squareIB);



		char flatColorVertexSrc[] = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

	
			void main()
			{		
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}

		)";

		char flatColorFragmentSrc[] = R"(
			#version 330 core
			layout(location = 0) out vec4 a_Color;
			uniform vec3 u_Color;
			void main()
			{		
				a_Color = vec4(u_Color, 1.0f);
			}
		)";

		m_flatColorShader.reset(Neural::Shader::create(flatColorVertexSrc, flatColorFragmentSrc));
	}

	void onUpdate(Neural::Timestep timestep) override
	{
		if (Neural::Input::isKeyPressed(NL_KEY_W))
			m_CameraPosition.y += m_cameraMoveSpeed * timestep;

		else if (Neural::Input::isKeyPressed(NL_KEY_S))
			m_CameraPosition.y -= m_cameraMoveSpeed * timestep;

		if (Neural::Input::isKeyPressed(NL_KEY_A))
			m_CameraPosition.x -= m_cameraMoveSpeed * timestep;

		else if (Neural::Input::isKeyPressed(NL_KEY_D))
			m_CameraPosition.x += m_cameraMoveSpeed * timestep;


		if (Neural::Input::isKeyPressed(NL_KEY_Q))
			m_cameraRotation += m_cameraRotationSpeed * timestep;

		else if (Neural::Input::isKeyPressed(NL_KEY_E))
			m_cameraRotation -= m_cameraRotationSpeed * timestep;



		Neural::RenderCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Neural::RenderCommand::clear();

		m_CameraPosition.x -= m_deltaPos.x * m_xMultiplier;
		m_CameraPosition.y += m_deltaPos.y * m_yMultiplier;

		m_deltaPos = { 0.0f, 0.0f };

		m_Camera.setPosition(m_CameraPosition);
		m_Camera.setRotation(m_cameraRotation);

		Neural::Renderer::beginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		m_flatColorShader->bind();
		m_flatColorShader->uploadUniformFloat3("u_Color", m_color);

		int size = 20;

		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				glm::vec3 pos(x *0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Neural::Renderer::submit(m_flatColorShader, m_squareVA, transform);
			}
		}

		Neural::Renderer::submit(m_shader, m_vertexArray);

		Neural::Renderer::endScene();
	}

	virtual void onEvent(Neural::Event& event) override
	{
		Neural::EventDispatcher dispatcher(event);
		dispatcher.dispatch<Neural::MouseButtonPressedEvent>([&](Neural::MouseButtonPressedEvent& event) {
			if (event.getMouseButton() == NL_MOUSE_BUTTON_1)
			{
				
				m_mouseCursorPressed = true;
				return true;
			}
			return false;
		});

		dispatcher.dispatch<Neural::MouseButtonReleasedEvent>([&](Neural::MouseButtonReleasedEvent& event) {
			m_mouseCursorPressed = false;
			return true;
		});

		dispatcher.dispatch<Neural::MouseMovedEvent>([&](Neural::MouseMovedEvent& event) {
			
			if (m_mouseCursorPressed && Neural::Input::isKeyPressed(NL_KEY_LEFT_SHIFT))
			{
				m_deltaPos = event.getDelta();
				return true;
			}
			
			return false;
		});
	}

	virtual void onImGuiRender(Neural::Timestep timestep) override
	{
		static int counter = 0;
		static float last_value = 0;

		float delta = ((last_value - timestep) < 0) ? (0 - (last_value - timestep)) : (last_value - timestep);
		if (delta > 0.0005f)
		{
			last_value = timestep;
		}
		counter++;
		
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Colors", glm::value_ptr(m_color));
		ImGui::End();
		
		ImGui::Begin("Performance");
		ImGui::Text("FPS %.2f\nDeltatime %f", 1 / last_value, timestep.getMilliseconds());
		ImGui::End();
	}

	~ExampleLayer()
	{
	}

private:
	Neural::Ref<Neural::Shader> m_shader;
	Neural::Ref<Neural::VertexArray> m_vertexArray;


	Neural::Ref<Neural::Shader> m_flatColorShader;
	Neural::Ref<Neural::VertexArray> m_squareVA;
	glm::vec3 m_color;


	Neural::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	glm::vec2 m_deltaPos;
	float m_cameraMoveSpeed = 5.0f;
	
	float m_xMultiplier;
	float m_yMultiplier;

	float m_cameraRotation = 0.0f;
	float m_cameraRotationSpeed = 30.0f;

	bool m_mouseCursorPressed = false;

};



class Engine : public Neural::Application 
{
public:
	Engine()
	{
		pushLayer(new ExampleLayer);
	}

	~Engine(){}
};

Neural::Application* Neural::CreateApplication() 
{
	return new Engine;
}