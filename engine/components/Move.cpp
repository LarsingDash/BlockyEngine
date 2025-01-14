//
// Created by larsv on 14/01/2025.
//

#include "Move.hpp"

#include <gameObject/GameObject.hpp>
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

Move::Move(GameObject* gameObject, const char* tag, KeyInput up, KeyInput down) :
		Component(gameObject, tag, false), _up(up), _down (down){}

void Move::Start() {
	//Interaction with other GameObjects, Components or Modules, not this Component's data. For example:
	InputModule& inputModule = ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule();
	inputModule.AddKeyListener(_up, *this, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			this->gameObject->transform->Translate(0, -10);
		}
	});
	inputModule.AddKeyListener(_down, *this, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			this->gameObject->transform->Translate(0, 10);
		}
	});
}

void Move::Update(float delta) {
	//This logic is updated every frame
}

void Move::End() {
	InputModule& inputModule = ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule();
	inputModule.RemoveKeyListener(_up, *this);
	inputModule.RemoveKeyListener(_down, *this);
}

Component* Move::_clone(const GameObject& parent) {
	auto clone = new Move(*this);
	return clone;
}