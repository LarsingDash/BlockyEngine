//
// Created by larsv on 12/11/2024.
//

#include "WindowModule.hpp"

#include "logging/BLogger.hpp"
#include "BlockyEngine.hpp"
#include "components/renderables/SpriteRenderable.hpp"

WindowModule::WindowModule() : renderingModule(nullptr), inputModule(nullptr) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::string err("Couldn't init video: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err)

		return;
	}

	//Create window
	window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  WindowModule::WINDOW_WIDTH, WindowModule::WINDOW_HEIGHT,
							  SDL_WINDOW_SHOWN);
	if (!window) {
		std::string err("Couldn't create window: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err)

		SDL_Quit();
		return;
	}

	//Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::string err("Couldn't create _renderer: ");
		err += SDL_GetError();
		BLOCKY_ENGINE_ERROR(err)

		SDL_Quit();
		SDL_DestroyWindow(window);
		return;
	}
	
	renderingModule = std::make_unique<RenderingModule>(renderer);
	inputModule = std::make_unique<InputModule>();
}

WindowModule::~WindowModule() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void WindowModule::Update(float delta) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	inputModule->PollEvents();
	_render();

	SDL_RenderPresent(renderer);
}

void WindowModule::_render() {
	renderingModule->Render();
}

InputModule& WindowModule::GetInputModule() {
	if (!inputModule) {
		throw std::runtime_error("InputModule is not initialized.");
	}
	return *inputModule;
}

RenderingModule& WindowModule::GetRenderingModule() {
	if (!renderingModule) {
		throw std::runtime_error("RenderingModule is not initialized.");
	}
	return *renderingModule;
}
