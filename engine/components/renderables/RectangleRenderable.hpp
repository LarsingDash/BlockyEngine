//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_RECTANGLERENDERABLE_HPP
#define BLOCKYENGINE_RECTANGLERENDERABLE_HPP

#include <glm/glm.hpp>
#include "Renderable.hpp"

class RectangleRenderable : public Renderable {

public:
    RectangleRenderable(GameObject& gameObject, const char* tag, const glm::ivec4& color);
    ~RectangleRenderable() override = default;
    glm::ivec4 GetColor() const;

private:
    glm::ivec4 _color;
};


#endif //BLOCKYENGINE_RECTANGLERENDERABLE_HPP
