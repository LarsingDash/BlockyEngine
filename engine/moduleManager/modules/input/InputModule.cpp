#include "InputModule.hpp"
#include "SDL.h"
#include "BlockyEngine.hpp"

// Polls events for input and window states
void InputModule::PollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			default: break;

			case SDL_KEYUP:
			case SDL_KEYDOWN: {
				KeyState state = (event.type == SDL_KEYDOWN) ? KeyState::KEY_DOWN : KeyState::KEY_UP;
				auto key = _getKeyInput(event.key.keysym.sym);

				std::cout << "Processing key event: " << static_cast<int>(key) << ", state: "
						  << (state == KeyState::KEY_DOWN ? "down" : "up") << std::endl;

				// Directly lookup and invoke listeners from the map
				auto it = _keyListeners.find(key);
				if (it != _keyListeners.end()) {
					for (auto& listener : it->second) {
						listener(state);
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

				std::cout << "Processing mouse event: button " << static_cast<int>(button) << ", state: "
						  << (mouseState == MouseButtonState::BUTTON_DOWN ? "down" : "up")
						  << ", position: (" << x << ", " << y << ")" << std::endl;

				// Directly lookup and invoke listeners for the specific mouse button
				auto it = _mouseListeners.find(button);
				if (it != _mouseListeners.end()) {
					for (auto& listener : it->second) {
						listener(mouseState, x, y);
					}
				}
			}
				break;

			case SDL_QUIT: BlockyEngine::isRunning = false; break;
		}
	}
}

// Adds key listener for a specific key
void InputModule::AddKeyListener(KeyInput key, const std::function<void(KeyState)>& listener) {
	std::cout << "Adding key listener for key: " << static_cast<int>(key) << std::endl;
	_keyListeners[key].push_back(listener);
}

// Removes key listener for a specific key
void InputModule::RemoveKeyListener(KeyInput key, const std::function<void(KeyState)>& listener) {
	std::cout << "Removing key listener for key: " << static_cast<int>(key) << std::endl;
	auto& listeners = _keyListeners[key];
	auto it = std::find_if(listeners.begin(), listeners.end(),
						   [&listener](const std::function<void(KeyState)>& existingListener) {
							   return existingListener.target<void(*)(KeyState)>() == listener.target<void(*)(KeyState)>();
						   });
	if (it != listeners.end()) {
		listeners.erase(it);
	}
}

// Adds mouse listener for a specific button
void InputModule::AddMouseListener(MouseInput button, const std::function<void(MouseButtonState, int, int)>& listener) {
	std::cout << "Adding mouse listener for button: " << static_cast<int>(button) << std::endl;
	_mouseListeners[button].push_back(listener);
}

// Removes mouse listener for a specific button
void InputModule::RemoveMouseListener(MouseInput button, const std::function<void(MouseButtonState, int, int)>& listener) {
	std::cout << "Removing mouse listener for button: " << static_cast<int>(button) << std::endl;

	auto& listeners = _mouseListeners[button];
	auto it = std::find_if(listeners.begin(), listeners.end(),
						   [&listener](const std::function<void(MouseButtonState, int, int)>& existingListener) {
							   return existingListener.target<void(*)(MouseButtonState, int, int)>() == listener.target<void(*)(MouseButtonState, int, int)>();
						   });
	if (it != listeners.end()) {
		listeners.erase(it);
	}
}

// Gets the current mouse position
glm::ivec2 InputModule::GetCursorPosition() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return {x, y};
}

// Maps an SDL key code to the custom KeyInput
KeyInput InputModule::_getKeyInput(SDL_Keycode sdlKey) {
	return SDLKeyToCustomKey(sdlKey);
}
