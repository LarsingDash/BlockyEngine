//
// Created by 11896 on 15/11/2024.
//

#include "SpriteRenderable.hpp"

#include "gameObject/GameObject.hpp"

#include <utility>

SpriteRenderable::SpriteRenderable(GameObject* gameObject, const char* tag,
								   std::string filePath, std::string spriteTag,
								   RenderableType type, int layer, SpriteFlip spriteFlip) :
		Renderable(gameObject, tag, type, layer), _spriteFlip(spriteFlip),
		_filePath(std::move(filePath)), _spriteTag(std::move(spriteTag)) {}

Component* SpriteRenderable::_clone(const GameObject& parent) {
	auto clone = new SpriteRenderable(*this);
	return clone;
}

SpriteFlip SpriteRenderable::GetSpriteFlip() const {
	return _spriteFlip;
}

std::string SpriteRenderable::GetFilePath() const {
	return _filePath;
}

std::string SpriteRenderable::GetSpriteTag() const {
	return _spriteTag;
}

JSON_REGISTER_FROM_CUSTOM_CONSTRUCTOR(
		SpriteRenderable,
		json.at("spritePath").get<std::string>(),
		json.at("spriteTag").get<std::string>(),
		RenderableType::SPRITE,
		json.at("layer").get<int>(),
		json.at("spriteFlip").get<SpriteFlip>()
)

JSON_REGISTER_TO(
		SpriteRenderable,
		[](nlohmann::json& json, const SpriteRenderable& other) {
			json["layer"] = other.GetLayer();
			json["spritePath"] = other._filePath;
			json["spriteTag"] = other._spriteTag;
			json["spriteFlip"] = other._spriteFlip;
		}
)
