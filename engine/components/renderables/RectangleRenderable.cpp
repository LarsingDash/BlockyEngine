//
// Created by 11896 on 15/11/2024.
//

#include "RectangleRenderable.hpp"

RectangleRenderable::RectangleRenderable(GameObject& gameObject, const char* tag,
										 const glm::ivec4& color, bool isFilled) :
		Renderable(gameObject, tag, RenderableType::RECTANGLE),
		_color(color), _isFilled(isFilled) {}

glm::ivec4 RectangleRenderable::GetColor() const {
	return _color;
}

bool RectangleRenderable::IsFilled() const {
	return _isFilled;
}
void RectangleRenderable::SetColor(const glm::vec4& color) {
	this->_color = color;
}
