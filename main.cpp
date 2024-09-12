#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL.h>

#include <iostream>
#include <cmath>

//Methods
void input(SDL_Scancode key);
void init();
void draw();
void update(float delta);
void destroy();

//SDL
SDL_Window* window;
SDL_Renderer* renderer;
bool shouldQuit = false;

//Window
int windowWidth = 600;
int windowHeight = 800;
float windowWidthF = (float) windowWidth;
float windowHeightF = (float) windowHeight;

//Box
float x = 0, y = 0;
SDL_Texture* boxImage;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
	std::cout << "Launching" << std::endl;

	//Initialize video from SDL
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Couldn't init video: " << SDL_GetError() << std::endl;
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
	init();

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
					input(event.key.keysym.scancode);
					break;

				default:
					break;
			}
		}

		//Cycle
		update(static_cast<float>(delta) / 1000.f);
		draw();

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
	destroy();
	std::cout << "Quit" << std::endl;

	return 0;
}

void init() {
	SDL_RenderSetVSync(renderer, 1);

	int width, height, channels;
	unsigned char *image = stbi_load("../assets/triangle.png", &width, &height, &channels, STBI_rgb_alpha);

	if (!image) {
		std::cerr << "Couldn't load image" << std::endl;
	}

	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
			image, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32
	);
	boxImage = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

}

void input(SDL_Scancode key) {
	switch (key) {
		default:
			break;
		case SDL_SCANCODE_ESCAPE:
			shouldQuit = true;
			break;
	}
}

const float pi = 3.14159265f * 2.f;

void update(float delta) {
	x += 1 * delta;
	if (x >= pi) x -= pi;

	y += 1 * delta;
	if (y >= pi) y -= pi;
}

void draw() {
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	float size = 50;
	SDL_FRect rect{(sinf(x) + 1.f) / 2.f * (windowWidthF - size),
				   (cosf(y) * -1 + 1.f) / 2.f * (windowHeightF - size),
				   size, size};

	SDL_RenderCopyExF(renderer, boxImage, nullptr, &rect, (x / (pi) * 360) + 90, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

void destroy() {
	SDL_DestroyTexture(boxImage);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}