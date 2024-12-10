//
// Created by 11896 on 27/11/2024.
//

#include "MouseInput.hpp"

MouseInput SDLMouseButtonToCustomMouseButton(Uint8 sdlButton) {
	switch (sdlButton) {
		case SDL_BUTTON_LEFT:
			return MouseInput::BUTTON_LEFT;
		case SDL_BUTTON_RIGHT:
			return MouseInput::BUTTON_RIGHT;
		case SDL_BUTTON_MIDDLE:
			return MouseInput::BUTTON_MIDDLE;
		default:
			return MouseInput::BUTTON_LEFT;
	}
}