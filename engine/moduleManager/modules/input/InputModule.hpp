//
// Created by 11896 on 26/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_

#include <functional>
#include "KeyEvent.hpp"

class InputModule {
	public:
		InputModule(const InputModule&) = delete;
		InputModule& operator=(const InputModule&) = delete;

		static InputModule& GetInstance() {
			static InputModule instance;
			return instance;
		}
		void PollEvents();
		void AddKeyListener(const std::function<void(KeyEvent)>& listener);

	private:
		InputModule() = default;
		std::vector<std::function<void(KeyEvent)>> _keyListeners;
		static KeyInput _getKeyInput(SDL_Keycode sdlKey);
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_INPUT_INPUTMODULE_HPP_
