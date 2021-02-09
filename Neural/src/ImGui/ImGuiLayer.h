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

		virtual void onAttach();
		virtual void onDetach();
		virtual void onImGuiRender() override;

		void begin();
		void end();

	private:
		float c_time = 0.0f;
	};

}
