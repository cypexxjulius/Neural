#pragma once

#include "Neural/Core/Layer.h"
#include "Neural/Events/ApplicationEvent.h"
#include "Neural/Events/KeyEvent.h"
#include "Neural/Events/MouseEvent.h"

namespace Neural {

	class NEURAL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach();
		virtual void onDetach();
		virtual void onImGuiRender() override;

		void begin();
		void end();

	private:
		float m_time = 0.0f;
	};

}
