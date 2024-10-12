#include "BlockyEngine.h"
#include "Renderer/RendererFactory.h"
#include "Renderable/Texture.h"
#include "Renderable/Animation/Animation.hpp"
#include "Renderable/Animation/AnimatedSprite.hpp"

#include <iostream>

BlockyEngine::BlockyEngine(bool useHardware) : shouldQuit(false) {
    windowModule = new WindowModule();
    renderer = RendererFactory::createRenderer(windowModule->getWindow(), useHardware);
    inputModule = new InputModule();

    SDL_Color redColor = {255, 0, 0, 255};
    SDL_Color greenColor = {0, 255, 0, 255};
    renderManager.addRenderable(new Rectangle(100, 100, 200, 150, redColor));
    renderManager.addRenderable(new Circle(150, 150, 100, greenColor));

    SDL_Rect textureRect = {250, 250, 80, 80};
    Texture* textureRenderable = new Texture("../assets/ghost.png", renderer, textureRect);
    renderManager.addRenderable(textureRenderable);

    AnimatedSprite* animatedSprite = new AnimatedSprite("../assets/spritesheet.png",
                                                        renderer, 32, 32, 180, 180);
    Animation walkAnimation("idle", 0, 12, 0.1f, true);
    Animation attackAnimation("attack", 52, 60, 0.1f, true);
    animatedSprite->addAnimation(walkAnimation);
    animatedSprite->addAnimation(attackAnimation);
    animatedSprite->playAnimation("attack");

    renderManager.addRenderable(animatedSprite);
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
        float deltaTime = (curTicks - prevTicks) / 1000.0f;
        prevTicks = curTicks;

        processEvents();

        renderManager.updateAll(deltaTime);

        renderer->clear();

        renderManager.renderAll(renderer);

        renderer->present();

        frameCount++;
        fps += curTicks - prevTicks;
        if (fps >= fpsInterval) {
            std::cout << "FPS: " << frameCount
                      << " Renderable count: " << renderManager.getRenderableCount()
                      << std::endl;
            fps = 0;
            frameCount = 0;
        }
    }
}
