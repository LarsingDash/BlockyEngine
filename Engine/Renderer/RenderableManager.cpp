#include "RenderableManager.h"

void RenderableManager::addRenderable(Renderable* renderable) {
    renderables.push_back(renderable);
}

void RenderableManager::renderAll(IRenderer* renderer) {
    for (Renderable* renderable : renderables) {
        renderable->render(renderer);
    }
}
int RenderableManager::getRenderableCount() const {
    return static_cast<int>(renderables.size());
}
void RenderableManager::updateAll(float deltaTime) {
    for (Renderable* renderable : renderables) {
        renderable->update(deltaTime);
    }
}
RenderableManager::~RenderableManager() {
    for (Renderable* renderable : renderables) {
        delete renderable;
    }
}