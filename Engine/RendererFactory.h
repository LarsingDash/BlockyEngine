#pragma once

#include "IRenderer.h"
#include "SoftwareRenderer.h"
#include "HardwareRenderer.h"

class RendererFactory {
public:
    static IRenderer* createRenderer(SDL_Window* window, bool useHardware) {
        if (useHardware) {
            return new HardwareRenderer(window);
        } else {
            return new SoftwareRenderer(window);
        }
    }
};
