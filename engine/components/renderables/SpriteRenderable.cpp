//
// Created by 11896 on 15/11/2024.
//

#include "SpriteRenderable.hpp"

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

