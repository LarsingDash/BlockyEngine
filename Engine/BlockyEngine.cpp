#include "BlockyEngine.h"
#include "Renderer/RendererFactory.h"
#include "Renderable/Texture.h"
#include "Renderable/Animation/Animation.hpp"
#include "Renderable/Animation/AnimatedSprite.hpp"

#include <iostream>
AnimationController* animationController;
AnimatedSprite* animatedSprite;
Texture* backgroundTexture;

int positionX = 100;
BlockyEngine::BlockyEngine(bool useHardware) : shouldQuit(false) {
    windowModule = new WindowModule();
    renderer = RendererFactory::createRenderer(windowModule->getWindow(), useHardware);
    inputModule = new InputModule();
//
//    SDL_Color redColor = {255, 0, 0, 255};
//    SDL_Color greenColor = {0, 255, 0, 255};
//    renderManager.addRenderable(new Rectangle(100, 100, 200, 150, redColor));
//    renderManager.addRenderable(new Circle(150, 150, 100, greenColor));
    int windowWidth, windowHeight;
    SDL_GetWindowSize(windowModule->getWindow(), &windowWidth, &windowHeight);

    SDL_Rect backgroundRect = {0, 0, windowWidth, windowHeight};
    backgroundTexture = new Texture("../assets/Background.jpg", renderer, backgroundRect);
    renderManager.addRenderable(backgroundTexture);



    animationController = new AnimationController();
    animatedSprite = new AnimatedSprite("../assets/spritesheet.png", renderer, animationController, 32, 32, 250, 250);
    animationController->addAnimation(Animation("idle", 0, 12, 0.1f, true));
    animationController->addAnimation(Animation("run", 13, 20, 0.1f, true));
    animationController->addAnimation(Animation("jump", 26, 35, 0.1f, false));
    animationController->addAnimation(Animation("attack", 39, 47, 0.1f, true));
    animationController->addAnimation(Animation("die", 91, 97, 0.1f, false));
    renderManager.addRenderable(animatedSprite);
    animatedSprite->setPosition(positionX, 158);
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
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                    animationController->playAnimation("idle");
                    break;
                case SDL_SCANCODE_W:
                    animationController->playAnimation("run");
                    break;
                case SDL_SCANCODE_E:
                    animationController->playAnimation("jump");
                    break;
                case SDL_SCANCODE_R:
                    animationController->playAnimation("attack");
                    break;
                case SDL_SCANCODE_T:
                    animationController->playAnimation("die");
                    break;
                default:
                    break;
            }
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
