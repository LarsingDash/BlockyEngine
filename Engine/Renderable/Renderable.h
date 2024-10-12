#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../Renderer/IRenderer.h"

class Renderable {
public:
    virtual ~Renderable() {}
    virtual void update(float deltaTime) = 0;
    virtual void render(IRenderer* renderer) = 0;
};

#endif // RENDERABLE_H