#pragma once


namespace Neural
{
	class Event;
	class Timestep;

	class Layer
	{	
	public:
		Layer(const char* debugName);
		virtual ~Layer();
		
		virtual void onAttach();
		virtual void onDetach();
		virtual void onUpdate(Timestep timestep);
		virtual void onEvent(Event& event);
		virtual void onImGuiRender();

		inline const char* getName() const 
		{ 
			return m_debugName;  
		}
	protected:
		const char* m_debugName;
	};
}
