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
#include "moduleManager/modules/rendering/ImGuiRenderingModule.hpp"

class WindowModule : public ModuleWrapper {
	public:
		WindowModule();
		~WindowModule() override;

		void Update(float delta) override;

		RenderingModule& GetRenderingModule();
		InputModule& GetInputModule();
		ImGuiRenderingModule& GetGuiRenderingModule();

	private:
		void _render();

		constexpr static int WINDOW_WIDTH = 800;
		constexpr static int WINDOW_HEIGHT = 600;

		SDL_Window* _window;
		SDL_Renderer* _renderer;
		SDL_GLContext _context;

		std::unique_ptr<RenderingModule> _renderingModule;
		std::unique_ptr<InputModule> _inputModule;
		std::unique_ptr<ImGuiRenderingModule> _guiRenderingModule;
};

#endif //BLOCKYENGINE_WINDOWMODULE_HPP