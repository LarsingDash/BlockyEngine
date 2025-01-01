//
// Created by 11896 on 15/11/2024.
//

#include "EllipseRenderable.hpp"

#include "gameObject/GameObject.hpp"

EllipseRenderable::EllipseRenderable(GameObject* gameObject, const char* tag,
									 const glm::ivec4& color, int layer, bool isFilled)
		: Renderable(gameObject, tag, RenderableType::ELLIPSE, layer),
		  _color(color), _isFilled(isFilled) {}

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

JSON_REGISTER_FROM_CUSTOM_CONSTRUCTOR(
		EllipseRenderable,
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
		EllipseRenderable,
		[](nlohmann::json& json, const EllipseRenderable& other) {
			json["r"] = other._color.r;
			json["g"] = other._color.g;
			json["b"] = other._color.b;
			json["a"] = other._color.a;
			json["layer"] = other.GetLayer();
			json["filled"] = other._isFilled;
		}
)