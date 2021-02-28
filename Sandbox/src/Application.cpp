#include <Neural.h>
#include <imgui.h>

class ExampleLayer : public Neural::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{

		m_vertexArray = Neural::VertexArray::create();


		float vertices[] =
		{
			-0.5f,  -0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f,   -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,   0.5f,  0.0f, 0.8f, 0.2f, 0.2f, 1.0f
		};

		Neural::VertexBuffer* vertexBuffer = Neural::VertexBuffer::create(vertices, sizeof(vertices));

		Neural::BufferLayout layout = {
			{ Neural::ShaderDataType::Float3, "a_Position"},
			{ Neural::ShaderDataType::Float4, "a_Color"}
		};


		vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Neural::IndexBuffer* indexBuffer = Neural::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));

		m_vertexArray->setIndexBuffer(indexBuffer);

		char vertexSrc[] = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;		
			out vec4 v_Color;
	
			void main()
			{		
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
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

		m_shader = new Neural::Shader(vertexSrc, fragmentSrc);


		// Test


		m_squareVA = Neural::VertexArray::create();

		float squareVertices[] =
		{
			-0.75f,  -0.75f,  0.0f,
			 0.75f,   -0.75f, 0.0f,
			 0.75f,   0.75f,  0.0f,
			 -0.75f,   0.75f,  0.0f
		};

		Neural::VertexBuffer* squareVB = Neural::VertexBuffer::create(squareVertices, sizeof(squareVertices));
		squareVB->setLayout({
			{ Neural::ShaderDataType::Float3, "a_Position" }
		});

		m_squareVA->addVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		Neural::IndexBuffer* squareIB = Neural::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		m_squareVA->setIndexBuffer(squareIB);



		char squareVertexSrc[] = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
	
			void main()
			{		
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
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

		m_squareShader = new Neural::Shader(squareVertexSrc, squareFragmentSrc);
	}

	void onUpdate(Neural::Timestep timestep) override
	{
		if (Neural::Input::isKeyPressed(NL_KEY_W))
			m_CameraPosition.y -= m_cameraMoveSpeed * timestep;

		else if (Neural::Input::isKeyPressed(NL_KEY_S))
			m_CameraPosition.y += m_cameraMoveSpeed * timestep;

		if (Neural::Input::isKeyPressed(NL_KEY_A))
			m_CameraPosition.x += m_cameraMoveSpeed * timestep;

		else if (Neural::Input::isKeyPressed(NL_KEY_D))
			m_CameraPosition.x -= m_cameraMoveSpeed * timestep;


		if (Neural::Input::isKeyPressed(NL_KEY_Q))
			m_cameraRotation += m_cameraRotationSpeed * timestep;

		else if (Neural::Input::isKeyPressed(NL_KEY_E))
			m_cameraRotation -= m_cameraRotationSpeed * timestep;



		Neural::RenderCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Neural::RenderCommand::clear();

		m_Camera.setPosition(m_CameraPosition);
		m_Camera.setRotation(m_cameraRotation);

		Neural::Renderer::beginScene(m_Camera);

		Neural::Renderer::submit(m_squareShader, m_squareVA);

		Neural::Renderer::submit(m_shader, m_vertexArray);

		Neural::Renderer::endScene();
	}

	void onEvent(Neural::Event& event) override
	{
	}

	~ExampleLayer()
	{
		delete m_shader;
		delete m_vertexArray;

		delete m_squareShader;
		delete m_squareVA;
	}

private:
	Neural::Shader* m_shader;
	Neural::VertexArray* m_vertexArray;

	Neural::Shader* m_squareShader;
	Neural::VertexArray* m_squareVA;

	Neural::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_cameraMoveSpeed = 5.0f;
	
	float m_cameraRotation = 0.0f;
	float m_cameraRotationSpeed = 30.0f;
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