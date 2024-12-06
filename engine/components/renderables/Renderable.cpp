//
// Created by larsv on 13/11/2024.
//

#include "Renderable.hpp"

#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

Renderable::Renderable(GameObject* gameObject, const char* tag, RenderableType renderableType, int layer) :
		Component(gameObject, tag, true), _renderableType(renderableType), _layer(layer) {}

Renderable::~Renderable() = default;

void Renderable::Start() {
	ModuleManager::GetInstance().GetModule<WindowModule>().GetRenderingModule().AddRenderable(*this);
}

void Renderable::Update(float delta) {

}

void Renderable::End() {
	ModuleManager::GetInstance()
			.GetModule<WindowModule>()
			.GetRenderingModule()
			.RemoveRenderable(*this);
}
