#pragma once
#include "Events/Event.h"

namespace Neural
{
	class NEURAL_API Layer
	{	
	public:
		Layer(const char* debugName);
		virtual ~Layer();
		
		virtual void onAttach();
		virtual void onDetach();
		virtual void onUpdate();
		virtual void onEvent(Event& event);
		virtual void onImGuiRender();

		inline const char* getName() const 
		{ 
			return c_debugName;  
		}
	protected:
		const char* c_debugName;
	};
}
