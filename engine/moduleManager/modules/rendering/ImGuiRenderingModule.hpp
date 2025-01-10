//
// Created by 11896 on 06/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_IMGUIRENDERINGMODULE_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_IMGUIRENDERINGMODULE_HPP_

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <functional>
#include <string>
#include <SDL_video.h>

#include "moduleManager/ModuleWrapper.hpp"

class ImGuiRenderingModule : public ModuleWrapper {
	public:
		ImGuiRenderingModule(SDL_Window* window, SDL_Renderer* renderer, SDL_GLContext context);
		~ImGuiRenderingModule() override = default;

		void Init();
		void Render();
		void Update(float delta) override {}

		void AddComponent(const std::string& tag, std::function<void()> uiComponent);
		void RemoveComponent(const std::string& tag);

	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		SDL_GLContext _context;

		std::unordered_map<std::string, std::function<void()>> _uiComponents;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_IMGUIRENDERINGMODULE_HPP_
