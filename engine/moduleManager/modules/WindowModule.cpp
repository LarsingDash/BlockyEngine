//
// Created by larsv on 12/11/2024.
//

#include "WindowModule.hpp"

#include <cmath>
#include <SDL.h>

#include <iostream>

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
    auto& rect = dynamic_cast<RectangleRenderable&>(renderable);
    glm::ivec4 color = rect.GetColor();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    ComponentTransform& transform = *rect.componentTransform;
    SDL_FRect rectShape{
            transform.position.x - transform.scale.x / 2.f,
            transform.position.y - transform.scale.y / 2.f,
            transform.scale.x,
            transform.scale.y
    };
    SDL_RenderFillRectF(renderer, &rectShape);

}

void WindowModule::RenderEllipse(Renderable &renderable) {
    auto &ellipse = dynamic_cast<EllipseRenderable &>(renderable);
    glm::ivec4 color = ellipse.GetColor();

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    ComponentTransform &transform = *ellipse.componentTransform;

    float centerX = transform.position.x;
    float centerY = transform.position.y;
    float radiusX = transform.scale.x / 2.0f;
    float radiusY = transform.scale.y / 2.0f;

    for (float angle = 0; angle < 360.0f; angle += 1.0f) {
        float rad = angle * M_PI / 180.0f;
        float x = centerX + radiusX * cos(rad);
        float y = centerY + radiusY * sin(rad);
        SDL_RenderDrawPointF(renderer, x, y);
    }
}

void WindowModule::RenderSprite(Renderable &renderable) {

}



