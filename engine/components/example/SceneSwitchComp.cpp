//
// Created by larsv on 06/12/2024.
//

#include "SceneSwitchComp.hpp"

#include "sceneManager/SceneManager.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

SceneSwitchComp::SceneSwitchComp(GameObject* gameObject, const char* tag, const char* target) :
		Component(gameObject, tag), _target(target) {}

SceneSwitchComp::~SceneSwitchComp() = default;

Component* SceneSwitchComp::_clone(const GameObject& parent) {
	auto clone = new SceneSwitchComp(*this);
	return clone;
}

void SceneSwitchComp::Start() {
	InputModule& inputModule = ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule();
	
	inputModule.AddKeyListener(
			KeyInput::KEY_S, *this, [&target = _target](KeyState state) {
				if (state == KeyState::KEY_DOWN)
					SceneManager::GetInstance().SwitchScene(target);
			});
	
	inputModule.AddKeyListener(
			KeyInput::KEY_R, *this, [&target = _target](KeyState state) {
				if (state == KeyState::KEY_DOWN)
					SceneManager::GetInstance().RemoveScene(target);
			});
}

void SceneSwitchComp::Update(float delta) {}

void SceneSwitchComp::End() {
	InputModule& inputModule = ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule();
	
	inputModule.RemoveKeyListener(KeyInput::KEY_S, *this);
	inputModule.RemoveKeyListener(KeyInput::KEY_R, *this);
}
