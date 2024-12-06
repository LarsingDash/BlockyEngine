//
// Created by larsv on 12/11/2024.
//

#include "WindowModule.hpp"

#include <iostream>
#include "BlockyEngine.hpp"
#include "components/renderables/SpriteRenderable.hpp"

WindowModule::WindowModule() : _renderingModule(nullptr), _inputModule(nullptr) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Couldn't init video: " << SDL_GetError() << std::endl;
		return;
	}

	//Create window
	_window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							   WindowModule::WINDOW_WIDTH, WindowModule::WINDOW_HEIGHT,
							   SDL_WINDOW_SHOWN);
	if (!_window) {
		std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	//Renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer) {
		std::cerr << "Couldn't create _renderer: " << SDL_GetError() << std::endl;
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

