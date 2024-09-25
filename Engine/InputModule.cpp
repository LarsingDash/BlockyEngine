#include "InputModule.h"
#include <iostream>

void InputModule::handleExit(SDL_Scancode key, bool& shouldQuit) {
    if (key == SDL_SCANCODE_ESCAPE) {
        shouldQuit = true;
        std::cout << "Escape key pressed!" << std::endl;
    }
}
