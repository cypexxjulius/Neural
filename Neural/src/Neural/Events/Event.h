#pragma once

#include "Neural/Core/Core.h"

namespace Neural {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	
	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	#define EVENT_CLASS_TYPE(type)  static EventType getStaticType() { return EventType::##type;} \
									virtual EventType getEventType() const override { return getStaticType(); } \
									virtual inline const char * getName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; };
		
		/*
		* This is a pure parent Class, it can't be created only 
		* inherited, 
		* getEventType()		-> Type of the Event
		* getCategoryFlags()	-> Class flag of the Event
		* getName()				-> Name of the Event as a string literal
		*/
		class NEURAL_API Event {
			friend class EventDispatcher;
		public:
			virtual EventType getEventType() const = 0;
			virtual int getCategoryFlags() const = 0;
			static EventType getStaticType();
			virtual inline const char* getName() const = 0;
			inline bool IsInCategory(EventCategory category) {
				return getCategoryFlags() & category;
			}

		public:
			bool m_handled = false;

		};

		/*
		* Takes in a function witch is getting called 
		* if the event has occured
		*/
		class EventDispatcher {
		private:
			template<typename T>
			using EventFn = std::function<bool(T&)>;
		
			Event& m_Event;
		public:
			EventDispatcher(Event& event)
				: m_Event(event) {}

			template<typename T> 
			bool dispatch(EventFn<T> func) 
			{
				if (m_Event.getEventType() == T::getStaticType()) 
				{
					m_Event.m_handled = func(*(T*)&m_Event);
					return true;
				}
				return false;
			}
		};


		inline std::ostream& operator<<(std::ostream& os, const Event& event) 
		{
			return os << event.getName();
		}
}
