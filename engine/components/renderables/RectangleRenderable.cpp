//
// Created by 11896 on 15/11/2024.
//

#include "RectangleRenderable.hpp"

#include "gameObject/GameObject.hpp"

RectangleRenderable::RectangleRenderable(GameObject* gameObject, const char* tag,
										 const glm::ivec4& color, int layer, bool isFilled) :
		Renderable(gameObject, tag, RenderableType::RECTANGLE, layer),
		_color(color), _isFilled(isFilled) {}

Component* RectangleRenderable::_clone(const GameObject& parent) {
	auto clone = new RectangleRenderable(*this);
	return clone;
}

glm::ivec4 RectangleRenderable::GetColor() const {
	return _color;
}

bool RectangleRenderable::IsFilled() const {
	return _isFilled;
}
void RectangleRenderable::SetColor(const glm::vec4& color) {
	this->_color = color;
}

JSON_REGISTER_FROM_CUSTOM_CONSTRUCTOR(
		RectangleRenderable,
		glm::vec4{
				json.at("r").get<float>(),
				json.at("g").get<float>(),
				json.at("b").get<float>(),
				json.at("a").get<float>()
		},
		json.at("layer").get<int>(),
		json.at("filled").get<bool>()
)

JSON_REGISTER_TO(
		RectangleRenderable,
		[](nlohmann::json& json, const RectangleRenderable& other) {
			json["r"] = other._color.r;
			json["g"] = other._color.g;
			json["b"] = other._color.b;
			json["a"] = other._color.a;
			json["layer"] = other.GetLayer();
			json["filled"] = other._isFilled;
		}
)
