#pragma once

#include "Core/Core.h"

namespace Neural {

	struct MousePosition
	{
		float x, y;
	};

	class NEURAL_API Input
	{
	public:
		inline static bool isKeyPressed(int keycode) { return c_Instance->isKeyPressedImpl(keycode); }

		inline static bool isMouseButtonPressed(int button) { return c_Instance->isMouseButtonPressedImpl(button); }
		inline static MousePosition getMousePosition() { return c_Instance->getMousePositionImpl(); }

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;

		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual MousePosition getMousePositionImpl() = 0;
	private:
		static Input* c_Instance;
	};

}