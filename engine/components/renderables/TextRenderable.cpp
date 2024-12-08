//
// Created by 11896 on 06/12/2024.
//

#include "TextRenderable.hpp"

TextRenderable::TextRenderable(GameObject& gameObject, const char* tag, std::string  text, const glm::ivec4& color, TTF_Font* font) :
		Renderable(gameObject, tag, RenderableType::TEXT),
		_text(std::move(text)), _color(color), _font(font) {}

TextRenderable::~TextRenderable() = default;

void TextRenderable::SetText(const std::string& newText) {
	_text = newText;
}

const std::string& TextRenderable::GetText() const {
	return _text;
}

const glm::ivec4& TextRenderable::GetColor() const {
	return _color;
}

TTF_Font* TextRenderable::GetFont() const {
	return _font;
}