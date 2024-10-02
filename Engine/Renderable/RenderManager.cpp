#include "RenderManager.h"

void RenderManager::addRenderable(Renderable* renderable) {
    renderables.push_back(renderable);
}

void RenderManager::renderAll(IRenderer* renderer) {
    for (Renderable* renderable : renderables) {
        renderable->render(renderer);
    }
}

RenderManager::~RenderManager() {
    for (Renderable* renderable : renderables) {
        delete renderable;
    }
}