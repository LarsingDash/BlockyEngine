//
// Created by larsv on 12/11/2024.
//

#include "WindowModule.hpp"

#include <cmath>
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	ProcessEvents();
	Render();

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

void WindowModule::ProcessEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			default:
				break;
			case SDL_KEYDOWN: {
				SDL_Scancode key = event.key.keysym.scancode;
				switch (key) {
					default:
						break;
					case SDL_SCANCODE_ESCAPE:
						BlockyEngine::isRunning = false;
						break;
				}
			}
				break;
			case SDL_QUIT:
				BlockyEngine::isRunning = false;
				break;
		}
	}
}

void WindowModule::Render() {
	SDL_SetRenderDrawColor(renderer, 225, 25, 25, 255);

	//Render every rectangle
	//TODO Actually render based on RenderableType when we have those :)
	for (const Renderable& renderable: renderables) {
		ComponentTransform& transform = *renderable.componentTransform;

		//Build FRect with position being the center of the rectangle
		SDL_FRect rect{
				(transform.position.x - transform.scale.x / 2.f),
				(transform.position.y - transform.scale.y / 2.f),
				(transform.scale.x),
				(transform.scale.y),
		};

		//Precalculate rotation angles
		float radAngle = transform.rotation * static_cast<float>(M_PI) / 180.0f;
		float cosA = std::cos(radAngle);
		float sinA = std::sin(radAngle);

		//Rectangle corners before rotation
		SDL_FPoint points[5] = {
				{rect.x,          rect.y},    //TopLeft
				{rect.x + rect.w, rect.y},    //TopRight
				{rect.x + rect.w, rect.y + rect.h},    //BottomRight
				{rect.x,          rect.y + rect.h},    //BottomLeft
				{rect.x,          rect.y} //TopLeft again to close the loop
		};

		//Rotate all points around the center
		float centerX = rect.x + rect.w / 2;
		float centerY = rect.y + rect.h / 2;
		for (auto& point: points) {
			float dx = point.x - centerX;
			float dy = point.y - centerY;
			point.x = centerX + dx * cosA - dy * sinA;
			point.y = centerY + dx * sinA + dy * cosA;
		}

		//Draw lines from list of points
		SDL_RenderDrawLinesF(renderer, points, 5);
	}
}
