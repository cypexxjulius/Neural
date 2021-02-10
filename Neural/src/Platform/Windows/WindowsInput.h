#pragma once

#include "Neural/Core/Input.h"

namespace Neural
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual MousePosition getMousePositionImpl() override;
	};
}
