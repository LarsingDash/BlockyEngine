#include "BlockyEngine.h"
#include <iostream>

BlockyEngine::BlockyEngine() : shouldQuit(false) {
    windowModule = new WindowModule();
    renderingModule = new RenderingModule(windowModule->getWindow());
    inputModule = new InputModule();
}

BlockyEngine::~BlockyEngine() {
    delete windowModule;
    delete renderingModule;
    delete inputModule;
}

void BlockyEngine::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            shouldQuit = true;
        } else if (event.type == SDL_KEYDOWN) {
            inputModule->handleExit(event.key.keysym.scancode, shouldQuit);
        }
    }
}

void BlockyEngine::run() {
    Uint32 prevTicks = SDL_GetTicks();
    Uint32 fpsInterval = 1000;
    Uint32 fps = 0, frameCount = 0;

    while (!shouldQuit) {
        Uint32 curTicks = SDL_GetTicks();
        Uint32 delta = curTicks - prevTicks;
        prevTicks = curTicks;

        processEvents();
        renderingModule->update(static_cast<float>(delta) / 1000.f);
        renderingModule->draw();

        frameCount++;
        fps += delta;
        if (fps >= fpsInterval) {
            std::cout << "FPS: " << frameCount << std::endl;
            fps = 0;
            frameCount = 0;
        }
    }
}
