//
// Created by 11896 on 26/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_

#include <functional>
#include "KeyEvent.hpp"

class InputModule {
	public:
		InputModule() = default;
		InputModule(const InputModule&) = default;
		InputModule& operator=(const InputModule&) = delete;

		void PollEvents();
		void AddKeyListener(const std::function<void(KeyEvent)>& listener);
		void RemoveKeyListener(const std::function<void(KeyEvent)>& listener);

	private:
		std::vector<std::function<void(KeyEvent)>> _keyListeners;
		static KeyInput _getKeyInput(SDL_Keycode sdlKey);
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_
