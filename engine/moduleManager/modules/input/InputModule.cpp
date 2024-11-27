//
// Created by 11896 on 26/11/2024.
//

#include "InputModule.hpp"
#include "SDL.h"
#include "BlockyEngine.hpp"
#include "MouseInput.hpp"

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
				auto key = _getKeyInput(event.key.keysym.sym);
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

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP: {
				MouseButtonState mouseState = (event.type == SDL_MOUSEBUTTONDOWN) ? MouseButtonState::BUTTON_DOWN : MouseButtonState::BUTTON_UP;

				auto button = SDLMouseButtonToCustomMouseButton(event.button.button);
				int x = event.button.x;
				int y = event.button.y;

				MouseEvent mouseEvent(button, mouseState, x, y);

				std::cout << "Processing mouse event: button " << static_cast<int>(button) << ", state: "
						  << (mouseState == MouseButtonState::BUTTON_DOWN ? "down" : "up")
						  << ", position: (" << x << ", " << y << ")" << std::endl;
				for (auto& listener : _mouseListeners) {
					if (listener) {
						listener(mouseEvent);
					} else {
						std::cerr << "Invalid listener detected!" << std::endl;
					}
				}
			}
				break;

			case SDL_QUIT: BlockyEngine::isRunning = false; break;
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

void InputModule::AddMouseListener(const std::function<void(MouseEvent)>& listener) {
	std::cout << "Adding mouse listener" << std::endl;
	_mouseListeners.push_back(listener);
}

void InputModule::RemoveMouseListener(const std::function<void(MouseEvent)>& listener) {
	std::cout << "Removing mouse listener" << std::endl;

	auto it = std::find_if(_mouseListeners.begin(), _mouseListeners.end(),
						   [&listener](const std::function<void(MouseEvent)>& existingListener) {
							   return existingListener.target<void(*)(MouseEvent)>() == listener.target<void(*)(MouseEvent)>();
						   });

	if (it != _mouseListeners.end()) {
		_mouseListeners.erase(it);
	}
}
std::pair<int, int> InputModule::GetCursorPosition() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return {x, y};
}