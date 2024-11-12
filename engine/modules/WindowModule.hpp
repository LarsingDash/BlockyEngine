//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_WINDOWMODULE_HPP
#define BLOCKYENGINE_WINDOWMODULE_HPP

#include <SDL_render.h>

#include "modules/core/ModuleWrapper.hpp"

class WindowModule : public ModuleWrapper {
	public:
		WindowModule();
		~WindowModule() override;
		void Update(float delta) override;

	private:
		constexpr static int WINDOW_WIDTH = 800;
		constexpr static int WINDOW_HEIGHT = 600;

		SDL_Window* window;
		SDL_Renderer* renderer;
};


#endif //BLOCKYENGINE_WINDOWMODULE_HPP
