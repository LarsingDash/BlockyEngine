#pragma once
#include <SDL.h>

class InputModule {
public:
    void handleExit(SDL_Scancode key, bool& shouldQuit);
};
