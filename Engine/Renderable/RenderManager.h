#pragma once

#include <vector>
#include "Renderable.h"

class RenderManager {
private:
    std::vector<Renderable*> renderables;

public:
    void addRenderable(Renderable* renderable);

    void renderAll(IRenderer* renderer);

    ~RenderManager();
};