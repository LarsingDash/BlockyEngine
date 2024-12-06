//
// Created by 11896 on 06/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_IMGUIRENDERINGMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_IMGUIRENDERINGMODULE_HPP_

#include "moduleManager/ModuleWrapper.hpp"
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <functional>

class ImGuiRenderingModule : public ModuleWrapper {
	public:
		ImGuiRenderingModule(SDL_Window* window, SDL_Renderer* renderer, SDL_GLContext context);
		~ImGuiRenderingModule() override = default;

		void Init();
		void Render();
		void Update(float delta) override {}

		void AddComponent(std::function<void()> uiComponent) {}

	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		SDL_GLContext _context;

		std::vector<std::function<void()>> _uiComponents;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_IMGUIRENDERINGMODULE_HPP_
