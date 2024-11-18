//
// Created by 11896 on 15/11/2024.
//

#include "SpriteRenderable.hpp"

#include <utility>

SpriteRenderable::SpriteRenderable(GameObject& gameObject, const char* tag,
								   std::string filePath, std::string spriteTag) :
		Renderable(gameObject, tag, RenderableType::SPRITE),
		_filePath(std::move(filePath)), _spriteTag(std::move(spriteTag)) {}

std::string SpriteRenderable::GetFilePath() const {
	return _filePath;
}

std::string SpriteRenderable::GetSpriteTag() const {
	return _spriteTag;
}
