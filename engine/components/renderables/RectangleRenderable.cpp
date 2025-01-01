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

void RectangleRenderable::FromJson(GameObject& recipient, const nlohmann::json& jsonObject) {
	recipient.AddComponent<RectangleRenderable>(
			jsonObject.at("tag").get<std::string>().c_str(),
			glm::vec4{
					jsonObject.at("r").get<float>(),
					jsonObject.at("g").get<float>(),
					jsonObject.at("b").get<float>(),
					jsonObject.at("a").get<float>()
			},
			jsonObject.at("layer").get<int>(),
			jsonObject.at("filled").get<bool>()
	);
}

nlohmann::json RectangleRenderable::ToJson(const RectangleRenderable& other) {
	return nlohmann::json{
			{"tag", other.tag},
			{"r", other._color.r},
			{"g", other._color.g},
			{"b", other._color.b},
			{"a", other._color.a},
			{"layer", other.GetLayer()},
			{"filled", other._isFilled},
	};
}
