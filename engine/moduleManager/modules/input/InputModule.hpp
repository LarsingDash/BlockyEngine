//
// Created by 11896 on 26/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_

#include <functional>
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"
#include "MouseInput.hpp"
#include "glm/vec2.hpp"

class InputModule {
	public:
		InputModule() = default;

		void PollEvents();
		void AddKeyListener(KeyInput key, const std::function<void(KeyState)>& listener);
		void RemoveKeyListener(KeyInput key, const std::function<void(KeyState)>& listener);
		void AddMouseListener(MouseInput button, const std::function<void(MouseButtonState, int, int)>& listener);
		void RemoveMouseListener(MouseInput button, const std::function<void(MouseButtonState, int, int)>& listener);
		static glm::ivec2 GetCursorPosition();

	private:
		std::unordered_map<KeyInput, std::vector<std::function<void(KeyState)>>> _keyListeners;
		std::unordered_map<MouseInput, std::vector<std::function<void(MouseButtonState, int, int)>>> _mouseListeners;
		static KeyInput _getKeyInput(SDL_Keycode sdlKey);
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_
