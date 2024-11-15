//
// Created by 11896 on 15/11/2024.
//

#include <iostream>
#include "RenderingModule.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "components/renderables/SpriteRenderable.hpp"

RenderingModule::RenderingModule(SDL_Renderer *renderer) : renderer(renderer) {}

void RenderingModule::Render(const std::vector<std::reference_wrapper<Renderable>>& renderables) {
    for (Renderable &renderable : renderables) {
        switch (renderable.GetRenderableType()) {
            case RECTANGLE:
                RenderRectangle(renderable);
                break;
            case ELLIPSE:
                RenderEllipse(renderable);
                break;
            case SPRITE:
                RenderSprite(renderable);
                break;
        }
    }
}

void RenderingModule::RenderRectangle(Renderable &renderable) {
    auto &rect = reinterpret_cast<RectangleRenderable &>(renderable);
    glm::ivec4 color = rect.GetColor();
    ComponentTransform &transform = *rect.componentTransform;

    int x1 = static_cast<int>(transform.position.x - transform.scale.x / 2.f);
    int y1 = static_cast<int>(transform.position.y - transform.scale.y / 2.f);
    int x2 = static_cast<int>(transform.position.x + transform.scale.x / 2.f);
    int y2 = static_cast<int>(transform.position.y + transform.scale.y / 2.f);
    boxRGBA(renderer, x1, y1, x2, y2, color.r, color.g, color.b, color.a);
}

void RenderingModule::RenderEllipse(Renderable &renderable) {
    auto &ellipse = reinterpret_cast<EllipseRenderable &>(renderable);
    glm::ivec4 color = ellipse.GetColor();

    ComponentTransform &transform = *ellipse.componentTransform;

    int centerX = static_cast<int>(transform.position.x);
    int centerY = static_cast<int>(transform.position.y);
    int radiusX = static_cast<int>(transform.scale.x / 2.0f);
    int radiusY = static_cast<int>(transform.scale.y / 2.0f);

    filledEllipseRGBA(renderer, centerX, centerY, radiusX, radiusY, color.r, color.g, color.b, color.a);
}

void RenderingModule::RenderSprite(Renderable &renderable) {

}
