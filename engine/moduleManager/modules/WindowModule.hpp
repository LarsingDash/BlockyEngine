//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_WINDOWMODULE_HPP
#define BLOCKYENGINE_WINDOWMODULE_HPP

#include <SDL_render.h>
#include <vector>

#include "moduleManager/ModuleWrapper.hpp"
#include "moduleManager/modules/rendering/RenderingModule.hpp"
#include "moduleManager/modules/input/InputModule.hpp"

class WindowModule : public ModuleWrapper {
	public:
		WindowModule();
		~WindowModule() override;

		void Update(float delta) override;

		RenderingModule& GetRenderingModule();
		InputModule& GetInputModule();
	private:
		void _render();

		constexpr static int WINDOW_WIDTH = 800;
		constexpr static int WINDOW_HEIGHT = 600;

		SDL_Window* window;
		SDL_Renderer* renderer;
		std::unique_ptr<RenderingModule> renderingModule;
		std::unique_ptr<InputModule> inputModule;
};

#endif //BLOCKYENGINE_WINDOWMODULE_HPP