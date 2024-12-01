//
// Created by 11896 on 01/12/2024.
//

#include "KeyboardInputComponent.hpp"

KeyboardInputComponent::KeyboardInputComponent(GameObject& parent, const char* tag, GameObject& animatedObject)
		: Component(parent, tag), _animatedObject(animatedObject) {}

void KeyboardInputComponent::Start() {
	auto& animatedSprite = _animatedObject.AddComponent<AnimationRenderable>(
			"animTag", "../assets/character_spritesheet.png",
			"spriteTag", 32, 32
	);

	_animationController = _animatedObject.GetComponent<AnimationController>();
	_animationController->AddAnimation("idle", 0, 11, 0.15f, true);
	_animationController->AddAnimation("run", 12, 19, 0.1f, true);
	_animationController->AddAnimation("jump", 27, 35, 0.1f, false);

	_inputModule.AddKeyListener(KeyInput::KEY_Q, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("idle");
		}
	});
	_inputModule.AddKeyListener(KeyInput::KEY_W, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("run");
		}
	});
	_inputModule.AddKeyListener(KeyInput::KEY_E, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("jump");
		}
	});
	_inputModule.AddKeyListener(KeyInput::KEY_ESCAPE, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			End();
		}
	});
}

void KeyboardInputComponent::Update(float delta) {
}

void KeyboardInputComponent::End() {
	_inputModule.RemoveKeyListener(KeyInput::KEY_Q, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("idle");
		}
	});
	_inputModule.RemoveKeyListener(KeyInput::KEY_W, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("run");
		}
	});
	_inputModule.RemoveKeyListener(KeyInput::KEY_E, [this](KeyState state) {
		if (state == KeyState::KEY_DOWN) {
			ChangeAnimation("jump");
		}
	});
}

void KeyboardInputComponent::ChangeAnimation(const std::string& animationName) {
	if (_animationController) {
		_animationController->PlayAnimation(animationName);
	}
}
