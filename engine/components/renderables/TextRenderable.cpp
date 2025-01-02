//
// Created by 11896 on 06/12/2024.
//

#include "TextRenderable.hpp"

#include "gameObject/GameObject.hpp"

TextRenderable::TextRenderable(GameObject* gameObject, const char* tag, std::string text,
							   const glm::ivec4& color, std::string fontPath, int fontSize, int layer) :
		Renderable(gameObject, tag, RenderableType::TEXT, layer),
		_text(std::move(text)), _color(color), _fontPath(std::move(fontPath)), _fontSize(fontSize) {
	_font = TTF_OpenFont(_fontPath.c_str(), _fontSize);
}

TextRenderable::~TextRenderable() {
	TTF_CloseFont(_font);
}

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

Component* TextRenderable::_clone(const GameObject& parent) {
	auto clone = new TextRenderable(*this);
	return clone;
}

JSON_REGISTER_FROM_CUSTOM_CONSTRUCTOR(
		TextRenderable,
		json.at("text").get<std::string>(),
		glm::ivec4{
				json.at("r").get<int>(),
				json.at("g").get<int>(),
				json.at("b").get<int>(),
				json.at("a").get<int>(),
		},
		json.at("fontPath").get<std::string>(),
		json.at("fontSize").get<int>()
)

JSON_REGISTER_TO(
		TextRenderable,
		[](nlohmann::json& json, const TextRenderable& other) {
			json["text"] = other._text;
			json["r"] = other._color.r;
			json["g"] = other._color.g;
			json["b"] = other._color.b;
			json["a"] = other._color.a;

			json["fontPath"] = other._fontPath;
			json["fontSize"] = other._fontSize;
		}
)