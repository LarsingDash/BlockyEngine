//
// Created by larsv on 12/11/2024.
//

#include "WindowModule.hpp"

#include <cmath>
#include <SDL.h>

#include <iostream>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "BlockyEngine.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"

WindowModule::WindowModule() {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Couldn't init video: " << SDL_GetError() << std::endl;
        return;
    }

    //Create window
    window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WindowModule::WINDOW_WIDTH, WindowModule::WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    //Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        SDL_DestroyWindow(window);
        return;
    }
}

WindowModule::~WindowModule() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void WindowModule::Update(float delta) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    ProcessEvents();
    Render();

    SDL_RenderPresent(renderer);
}

void WindowModule::AddRenderable(Renderable &renderable) {
    renderables.emplace_back(renderable);
}

void WindowModule::RemoveRenderable(Renderable &renderable) {
    auto it = std::find_if(renderables.begin(), renderables.end(),
                           [&renderable](const std::reference_wrapper<Renderable> &other) {
                               return &renderable == &other.get();
                           });

    if (it != renderables.end()) {
        renderables.erase(it);
    }
}

void WindowModule::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            default:
                break;
            case SDL_KEYDOWN: {
                SDL_Scancode key = event.key.keysym.scancode;
                switch (key) {
                    default:
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        BlockyEngine::isRunning = false;
                        break;
                }
            }
                break;
            case SDL_QUIT:
                BlockyEngine::isRunning = false;
                break;
        }
    }
}

void WindowModule::Render() {
    SDL_SetRenderDrawColor(renderer, 225, 25, 25, 255);

    for (Renderable &renderable: renderables) {
        switch (renderable.GetRenderableType()) {
            case RECTANGLE: {
                RenderRectangle(renderable);
               break;
            }
            case ELLIPSE:
                RenderEllipse(renderable);
                break;
            case SPRITE:
                RenderSprite(renderable);
                break;
        }
    }

}

void WindowModule::RenderRectangle(Renderable &renderable) {
    auto& rect = reinterpret_cast<RectangleRenderable&>(renderable);
    glm::ivec4 color = rect.GetColor();
    ComponentTransform& transform = *rect.componentTransform;

    int x1 = static_cast<int>(transform.position.x - transform.scale.x / 2.f);
    int y1 = static_cast<int>(transform.position.y - transform.scale.y / 2.f);
    int x2 = static_cast<int>(transform.position.x + transform.scale.x / 2.f);
    int y2 = static_cast<int>(transform.position.y + transform.scale.y / 2.f);
    boxRGBA(renderer, x1, y1, x2, y2, color.r, color.g, color.b, color.a);
}

void WindowModule::RenderEllipse(Renderable &renderable) {
    auto &ellipse = reinterpret_cast<EllipseRenderable &>(renderable);
    glm::ivec4 color = ellipse.GetColor();

    ComponentTransform &transform = *ellipse.componentTransform;

    int centerX = static_cast<int>(transform.position.x);
    int centerY = static_cast<int>(transform.position.y);
    int radiusX = static_cast<int>(transform.scale.x / 2.0f);
    int radiusY = static_cast<int>(transform.scale.y / 2.0f);

    filledEllipseRGBA(renderer, centerX, centerY, radiusX, radiusY, color.r, color.g, color.b, color.a);

}

void WindowModule::RenderSprite(Renderable &renderable) {

}



