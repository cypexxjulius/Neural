#pragma once

#include "Neural/Core/Core.h"

namespace Neural {

	struct MousePosition
	{
		float x, y;
	};

	class Input
	{
	public:
		inline static bool isKeyPressed(int keycode) { return m_Instance->isKeyPressedImpl(keycode); }

		inline static bool isMouseButtonPressed(int button) { return m_Instance->isMouseButtonPressedImpl(button); }
		inline static MousePosition getMousePosition() { return m_Instance->getMousePositionImpl(); }

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;

		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual MousePosition getMousePositionImpl() = 0;
	private:
		static Input* m_Instance;
	};

}