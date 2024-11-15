//
// Created by 11896 on 15/11/2024.
//

#include "EllipseRenderable.hpp"

EllipseRenderable::EllipseRenderable(GameObject &gameObject, const char* tag, const glm::ivec4 &color)
        : Renderable(gameObject, tag, RenderableType::ELLIPSE), _color(color) {}

glm::ivec4 EllipseRenderable::GetColor() const {
    return _color;
}