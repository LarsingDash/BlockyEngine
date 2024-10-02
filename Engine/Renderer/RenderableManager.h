#pragma once

#include <vector>
#include "../Renderable/Renderable.h"

class RenderableManager {
private:
    std::vector<Renderable*> renderables;

public:
    void addRenderable(Renderable* renderable);
    int getRenderableCount() const;
    void renderAll(IRenderer* renderer);

    ~RenderableManager();
};