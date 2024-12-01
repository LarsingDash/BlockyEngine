//
// Created by larsv on 13/11/2024.
//

#include "Renderable.hpp"

#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

Renderable::Renderable(GameObject& gameObject, const char* tag, RenderableType renderableType) :
		Component(gameObject, tag), _renderableType(renderableType) {}

Renderable::~Renderable() = default;

void Renderable::Start() {
	ModuleManager::getInstance()
			.getModule<WindowModule>()
			.GetRenderingModule()
			.AddRenderable(*this);
}

void Renderable::Update(float delta) {

}

void Renderable::End() {
	ModuleManager::getInstance()
			.getModule<WindowModule>()
			.GetRenderingModule()
			.RemoveRenderable(*this);
}

RenderableType Renderable::GetRenderableType() {
	return _renderableType;
}


