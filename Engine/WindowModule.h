#pragma once

#include <SDL.h>

class WindowModule {
public:
    WindowModule();
    ~WindowModule();
    SDL_Window* getWindow();

private:
    void init();
    void destroy();
    SDL_Window* window;
};