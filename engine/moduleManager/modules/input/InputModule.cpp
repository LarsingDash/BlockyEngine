//
// Created by 11896 on 26/11/2024.
//

#include "InputModule.hpp"
#include "SDL.h"
#include "BlockyEngine.hpp"

KeyInput InputModule::_getKeyInput(SDL_Keycode sdlKey) {
	return SDLKeyToCustomKey(sdlKey);
}

void InputModule::PollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			default: break;
			case SDL_KEYUP:
			case SDL_KEYDOWN: {
				KeyState state = (event.type == SDL_KEYDOWN) ? KeyState::KEY_DOWN : KeyState::KEY_UP;
				KeyInput key = _getKeyInput(event.key.keysym.sym);
				KeyEvent keyEvent(key, state);

				std::cout << "Processing key event: " << static_cast<int>(key) << ", state: "
						  << (state == KeyState::KEY_DOWN ? "down" : "up") << std::endl;
				for (auto& listener : _keyListeners) {
					if (listener) {
						listener(keyEvent);
					} else {
						std::cerr << "Invalid listener detected!" << std::endl;
					}
				}
			}
				break;
			case SDL_QUIT: BlockyEngine::isRunning = false;
				break;
		}
	}
}

void InputModule::AddKeyListener(const std::function<void(KeyEvent)>& listener) {
	std::cout << "Adding listener" << std::endl;
	_keyListeners.push_back(listener);
}


void InputModule::RemoveKeyListener(const std::function<void(KeyEvent)>& listener) {
	std::cout << "Removing listener" << std::endl;

	auto it = std::find_if(_keyListeners.begin(), _keyListeners.end(),
						   [&listener](const std::function<void(KeyEvent)>& existingListener) {
							   return existingListener.target<void(*)(KeyEvent)>() == listener.target<void(*)(KeyEvent)>();
						   });

	if (it != _keyListeners.end()) {
		_keyListeners.erase(it);
	}
}
