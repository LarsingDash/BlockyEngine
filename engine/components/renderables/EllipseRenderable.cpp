//
// Created by 11896 on 15/11/2024.
//

#include "EllipseRenderable.hpp"

EllipseRenderable::EllipseRenderable(GameObject* gameObject, const char* tag, const glm::ivec4& color, bool isFilled)
		: Renderable(gameObject, tag, RenderableType::ELLIPSE), _color(color), _isFilled(isFilled) {}

Component* EllipseRenderable::_clone(const GameObject& parent) {
	auto clone = new EllipseRenderable(*this);
	return clone;
}

glm::ivec4 EllipseRenderable::GetColor() const {
	return _color;
}

bool EllipseRenderable::IsFilled() const {
	return _isFilled;
}
