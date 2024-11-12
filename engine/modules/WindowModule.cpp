﻿//
// Created by larsv on 12/11/2024.
//

#include "WindowModule.hpp"

#include <SDL.h>

#include <iostream>

#include "BlockyEngine.hpp"

WindowModule::WindowModule() {
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
		std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		return;
	}
}

WindowModule::~WindowModule() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void WindowModule::Update(float delta) {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			default:
				break;
			case SDL_QUIT:
				BlockyEngine::isRunning = false;
				break;
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_Rect temp{0,0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_RenderFillRect(renderer, &temp);
	SDL_RenderPresent(renderer);
}
