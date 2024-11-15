//
// Created by 11896 on 15/11/2024.
//

#include "RectangleRenderable.hpp"


RectangleRenderable::RectangleRenderable(GameObject &gameObject, const char* tag, const glm::ivec4 &color)
        : Renderable(gameObject, tag, RenderableType::RECTANGLE), _color(color) {}

glm::ivec4 RectangleRenderable::GetColor() const {
    return _color;
}
