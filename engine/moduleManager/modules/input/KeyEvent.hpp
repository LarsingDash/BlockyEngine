//
// Created by 11896 on 26/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_KEYEVENT_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_KEYEVENT_HPP_

#include "SDL_keycode.h"
#include "KeyInput.hpp"

enum KeyState {
	KEY_UP,
	KEY_DOWN
};

struct KeyEvent {
	KeyInput key;
	KeyState state;

	KeyEvent(KeyInput key, KeyState state)
			: key(key), state(state) {}
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_KEYEVENT_HPP_
