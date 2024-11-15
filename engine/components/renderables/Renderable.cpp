//
// Created by larsv on 13/11/2024.
//

#include "Renderable.hpp"

#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

Renderable::Renderable(GameObject& gameObject, const char* tag, RenderableType renderableType) : Component(gameObject, tag), _renderableType(renderableType) {}

Renderable::~Renderable() = default;

void Renderable::Start() {
	ModuleManager::getInstance().getModule<WindowModule>().AddRenderable(*this);
}

void Renderable::Update(float delta) {
	componentTransform->rotation = componentTransform->rotation + 90.f * delta;
	if (componentTransform->rotation >= 360.f) componentTransform->rotation -= 360;
}

void Renderable::End() {
	ModuleManager::getInstance().getModule<WindowModule>().RemoveRenderable(*this);
}

RenderableType Renderable::GetRenderableType() {
    return _renderableType;
}


