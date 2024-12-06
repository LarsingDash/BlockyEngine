﻿//
// Created by larsv on 06/12/2024.
//

#include "SceneSwitchComp.hpp"

#include "sceneManager/SceneManager.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

SceneSwitchComp::SceneSwitchComp(GameObject* gameObject, const char* tag, const char* target) :
		Component(gameObject, tag, false), _target(target) {}

SceneSwitchComp::~SceneSwitchComp() = default;

Component* SceneSwitchComp::_cloneImpl(GameObject& parent) {
	auto clone = new SceneSwitchComp(*this);
	return clone;
}

void SceneSwitchComp::Start() {
	ModuleManager::getInstance().getModule<WindowModule>().GetInputModule().AddKeyListener(
			KeyInput::KEY_S, *this, [&target = _target](KeyState state) {
				if (state == KeyState::KEY_DOWN)
					SceneManager::GetInstance()->SwitchScene(target);
			});
}

void SceneSwitchComp::Update(float delta) {}

void SceneSwitchComp::End() {
	ModuleManager::getInstance().getModule<WindowModule>().GetInputModule().RemoveKeyListener(KeyInput::KEY_S, *this);
}
