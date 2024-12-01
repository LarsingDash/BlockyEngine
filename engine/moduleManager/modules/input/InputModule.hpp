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
		void AddKeyListener(const std::function<void(KeyEvent)>& listener);
		void RemoveKeyListener(const std::function<void(KeyEvent)>& listener);
		void AddMouseListener(const std::function<void(MouseEvent)>& listener);
		void RemoveMouseListener(const std::function<void(MouseEvent)>& listener);
		static glm::ivec2 GetCursorPosition() ;

	private:
		std::vector<std::function<void(KeyEvent)>> _keyListeners;
		std::vector<std::function<void(MouseEvent)>> _mouseListeners;
		static KeyInput _getKeyInput(SDL_Keycode sdlKey);
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_
