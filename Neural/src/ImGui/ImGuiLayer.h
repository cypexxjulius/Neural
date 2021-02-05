#pragma once

#include "Core/Layer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Neural {

	class NEURAL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		~ImGuiLayer();

		void onUpdate();

		void onEvent(Event& event);

		void onAttach();
		void onDetach();
	private:
		bool onMouseButtonPressed(MouseButtonPressedEvent& event);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool onMouseScrolled(MouseScrolledEvent& event);
		bool onMouseMoved(MouseMovedEvent& event);
	
		bool onKeyTyped(KeyTypedEvent& event);

		bool onKeyPressed(KeyPressedEvent& event);
		bool onKeyReleased(KeyReleasedEvent& event);
		bool onWindowResize(WindowResizeEvent& event);


	private:
		float c_time = 0.0f;
	};

}
