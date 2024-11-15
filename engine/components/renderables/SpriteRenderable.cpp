//
// Created by 11896 on 15/11/2024.
//

#include "SpriteRenderable.hpp"

SpriteRenderable::SpriteRenderable(GameObject &gameObject, const char *tag, const std::string &filePath,
                                   const std::string &spriteTag) : Renderable(gameObject, tag, RenderableType::SPRITE),
                                                                   _filePath(filePath),
                                                                   _spriteTag(spriteTag) {}

std::string SpriteRenderable::GetFilePath() const {
    return _filePath;
}

std::string SpriteRenderable::GetSpriteTag() const {
    return _spriteTag;
}
