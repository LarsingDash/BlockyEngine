//
// Created by 11896 on 27/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_MOUSEEVENT_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_MOUSEEVENT_HPP_

#include "MouseInput.hpp"

enum class MouseButtonState {
	BUTTON_UP,
	BUTTON_DOWN
};

struct MouseEvent {
	MouseInput button;
	MouseButtonState state;
	int x, y;

	MouseEvent(MouseInput button, MouseButtonState state, int x, int y)
			: button(button), state(state), x(x), y(y) {}
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_MOUSEEVENT_HPP_
