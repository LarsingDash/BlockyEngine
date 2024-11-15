//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_ELLIPSERENDERABLE_HPP
#define BLOCKYENGINE_ELLIPSERENDERABLE_HPP
#include <glm/glm.hpp>
#include "Renderable.hpp"

class EllipseRenderable : public Renderable {
public:
    EllipseRenderable(GameObject& gameObject, const char* tag, const glm::ivec4& color);
    ~EllipseRenderable() override = default;
    [[nodiscard]] glm::ivec4 GetColor() const;

private:
    glm::ivec4 _color;
};


#endif //BLOCKYENGINE_ELLIPSERENDERABLE_HPP
