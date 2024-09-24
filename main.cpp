#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "GameObject/GameObjectManager.h"
#include <SDL.h>

#include <iostream>

//Methods
void Input(SDL_Scancode key);
void Init();
void Cycle(float delta);
void Destroy();

//SDL
SDL_Window* window;
SDL_Renderer* renderer;
bool shouldQuit = false;

//Window
int windowWidth = 600;
int windowHeight = 800;
float windowWidthF = (float) windowWidth;
float windowHeightF = (float) windowHeight;

//Managers
GameObjectManager* gameObjectManager;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
	std::cout << "Launching" << std::endl;

	//Initialize video from SDL
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Couldn't Init video: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Create window
	window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  windowWidth, windowHeight,
							  SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		return 1;
	}

	//Init
	Init();

	//Main loop vars
	SDL_Event event;

	Uint32 prevTicks = SDL_GetTicks();
	Uint32 frameCount = 0;
	Uint32 fps = 0;
	Uint32 fpsInterval = 1000;

	//Main loop
	while (!shouldQuit) {
		//Fps delta
		Uint32 curTicks = SDL_GetTicks();
		Uint32 delta = curTicks - prevTicks;
		prevTicks = curTicks;

		//Go through the queue of events (0 if there are none)
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				//Quit if event type is quit
				case SDL_QUIT:
					shouldQuit = true;
					break;

				case SDL_KEYDOWN:
					Input(event.key.keysym.scancode);
					break;

				default:
					break;
			}
		}

		//Cycle
		Cycle(static_cast<float>(delta) / 1000.f);

		//Fps count
		frameCount++;
		fps += delta;
		if (fps >= fpsInterval) {
			std::cout << "FPS: " << frameCount << std::endl;
			fps = 0;
			frameCount = 0;
		}
	}

	//Cleanup
	Destroy();
	std::cout << "Quit" << std::endl;

	return 0;
}

void Input(SDL_Scancode key) {
	switch (key) {
		default:
			break;
		case SDL_SCANCODE_ESCAPE:
			shouldQuit = true;
			break;
	}
}

void Init() {
	SDL_RenderSetVSync(renderer, true);

	gameObjectManager = new GameObjectManager();
}

void Cycle(float delta) {
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	gameObjectManager->OnUpdate(static_cast<float>(delta) / 1000.f);

	SDL_RenderPresent(renderer);
}

void Destroy() {
	delete gameObjectManager;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}