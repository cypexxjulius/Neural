#include "nlpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "Core/Application.h"

// Temporary 
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Neural {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") 
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}
	void ImGuiLayer::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		float time = (float)glfwGetTime();
		io.DeltaTime = time > 0.0 ? (time - c_time) : (1.0f / 60.0f);
		c_time = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::begin()
	{
	}

	void ImGuiLayer::end()
	{
	}

	void ImGuiLayer::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		// Enable Key controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		// Enable Key controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		// Enable Gamepad controls
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		// Enable docking
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		// Enble multi-viewport on windows
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::onDetach()
	{
	}
}