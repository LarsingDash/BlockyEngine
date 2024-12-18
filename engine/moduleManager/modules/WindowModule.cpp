//
// Created by larsv on 12/11/2024.
//

#include "WindowModule.hpp"

#include <SDL.h>

#include "logging/BLogger.hpp"
#include "BlockyEngine.hpp"
#include "components/renderables/SpriteRenderable.hpp"

WindowModule::WindowModule() : _renderingModule(nullptr), _inputModule(nullptr), _context() {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::string err("Couldn't init video: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err);

		return;
	}
	
	if (TTF_Init() != 0) {
		SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
		return;
	}

	//Create window
	const auto& configs = BlockyEngine::GetConfigs();
	_window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							   configs->windowWidth, configs->windowHeight,
							   configs->windowFlags);
	if (!_window) {
		std::string err("Couldn't create window: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err);

		SDL_Quit();
		return;
	}

	//Renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer) {
		std::string err("Couldn't create _renderer: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err);
		SDL_Quit();
		SDL_DestroyWindow(_window);
		return;
	}
	
	_renderingModule = std::make_unique<RenderingModule>(_renderer);
	_inputModule = std::make_unique<InputModule>();
	_guiRenderingModule = std::make_unique<ImGuiRenderingModule>(_window, _renderer, _context);
}

WindowModule::~WindowModule() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);

	SDL_Quit();
}

void WindowModule::Update(float delta) {
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);

	_inputModule->PollEvents();

	_render();
	_guiRenderingModule->Render();

	SDL_RenderPresent(_renderer);
}

void WindowModule::_render() {
	_renderingModule->Render();
}

InputModule& WindowModule::GetInputModule() {
	if (!_inputModule) {
		throw std::runtime_error("InputModule is not initialized.");
	}
	return *_inputModule;
}

RenderingModule& WindowModule::GetRenderingModule() {
	if (!_renderingModule) {
		throw std::runtime_error("RenderingModule is not initialized.");
	}
	return *_renderingModule;
}

ImGuiRenderingModule& WindowModule::GetGuiRenderingModule() {
	if (!_guiRenderingModule) {
		throw std::runtime_error("GUI RenderingModule is not initialized.");
	}
	return *_guiRenderingModule;
}

glm::ivec2 WindowModule::GetScreenSizeI() {
	int w, h;
	SDL_GetWindowSize(_window, &w, &h);
	return {w, h};
}

glm::vec2 WindowModule::GetScreenSizeF() {
	int w, h;
	SDL_GetWindowSize(_window, &w, &h);
	return {static_cast<float>(w), static_cast<float>(h)};
}
