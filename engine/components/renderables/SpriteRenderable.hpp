//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_SPRITERENDERABLE_HPP
#define BLOCKYENGINE_SPRITERENDERABLE_HPP


#include "Renderable.hpp"

class SpriteRenderable : public Renderable {
public:
    SpriteRenderable(GameObject &gameObject, const char *tag, const std::string &filePath, const std::string &spriteTag);
    ~SpriteRenderable() override = default;
    std::string GetFilePath() const;
    std::string GetSpriteTag() const;

private:
    std::string _spriteTag;
    std::string _filePath;

};


#endif //BLOCKYENGINE_SPRITERENDERABLE_HPP
