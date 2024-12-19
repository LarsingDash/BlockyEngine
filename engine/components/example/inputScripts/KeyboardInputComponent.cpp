//
// Created by 11896 on 01/12/2024.
//

#include "KeyboardInputComponent.hpp"

#include "gameObject/GameObject.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

KeyboardInputComponent::KeyboardInputComponent(GameObject* parent, const char* tag)
		: Component(parent, tag),
		  _inputModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule()){}

Component* KeyboardInputComponent::_clone(const GameObject& parent) {
	auto clone = new KeyboardInputComponent(*this);
	return clone;
}

void KeyboardInputComponent::Start() {
	_animationController = gameObject->GetComponent<AnimationController>();

	_inputModule.AddKeyListener(KeyInput::KEY_Q, *this, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("idle");
		}
	});
	_inputModule.AddKeyListener(KeyInput::KEY_W, *this, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("run");
		}
	});
	_inputModule.AddKeyListener(KeyInput::KEY_E, *this, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("jump");
		}
	});
	_inputModule.AddKeyListener(KeyInput::KEY_ESCAPE, *this, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			End();
		}
	});
}

void KeyboardInputComponent::Update(float delta) {
}

void KeyboardInputComponent::End() {
	_inputModule.RemoveKeyListener(KeyInput::KEY_Q, *this);
	_inputModule.RemoveKeyListener(KeyInput::KEY_W, *this);
	_inputModule.RemoveKeyListener(KeyInput::KEY_E, *this);
	_inputModule.RemoveKeyListener(KeyInput::KEY_ESCAPE, *this);
}

void KeyboardInputComponent::ChangeAnimation(const std::string& animationName) {
	if (_animationController) {
		_animationController->PlayAnimation(animationName);
	}
}
