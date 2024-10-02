#include "BlockyEngine.h"
#include "Renderer/RendererFactory.h"
#include "Renderable/Texture.h"

#include <iostream>

BlockyEngine::BlockyEngine(bool useHardware) : shouldQuit(false) {
    windowModule = new WindowModule();
    renderer = RendererFactory::createRenderer(windowModule->getWindow(), useHardware);
    inputModule = new InputModule();

//    SDL_Color clearColor = {0, 0, 255, 255};
//    renderer->setClearColor(clearColor);
    SDL_Color redColor = {255, 0, 0, 255};
    SDL_Color greenColor = {0, 255, 0, 255};



    renderManager.addRenderable(new Rectangle(100, 100, 200, 150, redColor));
    renderManager.addRenderable(new Circle(150, 150, 100, greenColor));

    SDL_Rect textureRect = {250, 250, 80, 80};
    Texture* textureRenderable = new Texture("E:\\C++\\Blocky Engine Minor\\BlockyEngine\\assets\\ghost.png", renderer, textureRect);
    renderManager.addRenderable(textureRenderable);
}

BlockyEngine::~BlockyEngine() {
    delete renderer;
    delete windowModule;
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

        renderer->clear();

        renderManager.renderAll(renderer);

        renderer->present();

        frameCount++;
        fps += delta;
        if (fps >= fpsInterval) {
            std::cout << "FPS: " << frameCount
                      << " Renderable count: " << renderManager.getRenderableCount()
                      << std::endl;
            fps = 0;
            frameCount = 0;
        }
    }
}
