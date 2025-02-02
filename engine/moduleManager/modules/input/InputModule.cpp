#include "InputModule.hpp"
#include <SDL_events.h>
#include <imgui_impl_sdl2.h>
#include "BlockyEngine.hpp"
#include "logging/BLogger.hpp"

// Polls events for input and window states
void InputModule::PollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type) {
			default:
				break;
			case SDL_KEYUP:
			case SDL_KEYDOWN: {
				KeyState state = (event.type == SDL_KEYDOWN) ? KeyState::KEY_DOWN : KeyState::KEY_UP;
				auto key = _getKeyInput(event.key.keysym.sym);

				// Directly lookup and invoke listeners from the map
				auto it = _keyListeners.find(key);
				if (it != _keyListeners.end()) {
					for (auto& listener : it->second) {
						listener.second(state);
					}
				}
			}
				if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
						case SDLK_END:
							TimeUtil::GetInstance().ToggleFpsCounter();
							break;
						case SDLK_PAGEUP:
							TimeUtil::GetInstance().IncreaseGameSpeed();
							break;
						case SDLK_HOME:
							TimeUtil::GetInstance().ResetGameSpeed();
							break;
						case SDLK_PAGEDOWN:
							TimeUtil::GetInstance().DecreaseGameSpeed();
							break;
						case SDLK_ESCAPE:
							BlockyEngine::isRunning = false;
							break;
						default:
							break;
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP: {
				MouseButtonState mouseState = (event.type == SDL_MOUSEBUTTONDOWN)
											  ? MouseButtonState::BUTTON_DOWN
											  : MouseButtonState::BUTTON_UP;
				auto button = SDLMouseButtonToCustomMouseButton(event.button.button);
				int x = event.button.x;
				int y = event.button.y;

				// Directly lookup and invoke listeners for the specific mouse button
				auto it = _mouseListeners.find(button);
				if (it != _mouseListeners.end()) {
					for (auto& listener : it->second) {
						listener.second(mouseState, x, y);
					}
				}
			}
				break;

			case SDL_QUIT:
				BlockyEngine::isRunning = false;
				break;
		}
	}
}

// Adds key listener for a specific key
void InputModule::AddKeyListener(KeyInput key, Component& owner, const std::function<void(KeyState)>& listener) {
	_keyListeners[key].emplace_back(&owner, listener);
}

// Removes key listener for a specific key
void InputModule::RemoveKeyListener(KeyInput key, Component& owner) {
	auto& listeners = _keyListeners[key];
	auto it = std::find_if(listeners.begin(), listeners.end(),
						   [&owner](const std::pair<Component*, std::function<void(KeyState)>>& listener) {
							   return listener.first == &owner;
						   });
	if (it != listeners.end()) {
		listeners.erase(it);
	}
}

// Adds mouse listener for a specific button
void InputModule::AddMouseListener(MouseInput button,
								   Component& owner,
								   const std::function<
										   void(MouseButtonState, int, int)
								   >& listener) {
	_mouseListeners[button].emplace_back(&owner, listener);
}

// Removes mouse listener for a specific button
void InputModule::RemoveMouseListener(MouseInput button, Component& owner) {
	auto& listeners = _mouseListeners[button];
	auto it = std::find_if(listeners.begin(), listeners.end(),
						   [&owner](const std::pair<
								   Component*,
								   std::function<
										   void(MouseButtonState, int, int)
								   >>& listener) {
							   return listener.first == &owner;
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