//
// Created by larsv on 12/11/2024.
//

#include "WindowModule.hpp"

#include <cmath>
#include <SDL.h>

#include <iostream>
#include "BlockyEngine.hpp"
#include "components/renderables/SpriteRenderable.hpp"

WindowModule::WindowModule() : renderingModule(nullptr), inputModule(nullptr) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Couldn't init video: " << SDL_GetError() << std::endl;
		return;
	}

	//Create window
	window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  WindowModule::WINDOW_WIDTH, WindowModule::WINDOW_HEIGHT,
							  SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	//Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cerr << "Couldn't create _renderer: " << SDL_GetError() << std::endl;
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
void WindowModule::AddRenderable(Renderable& renderable) {
	renderables.emplace_back(renderable);
}

void WindowModule::RemoveRenderable(Renderable& renderable) {
	auto it = std::find_if(renderables.begin(), renderables.end(),
						   [&renderable](const std::reference_wrapper<Renderable>& other) {
							   return &renderable == &other.get();
						   });

	if (it != renderables.end()) {
		renderables.erase(it);
	}
}


void WindowModule::_render() {
	renderingModule->Render(renderables);
}

InputModule& WindowModule::GetInputModule() {
	if (!inputModule) {
		throw std::runtime_error("InputModule is not initialized.");
	}
	return *inputModule;
}

