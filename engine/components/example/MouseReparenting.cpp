//
// Created by larsv on 01/12/2024.
//

#include "MouseReparenting.hpp"

#include "gameObject/GameObject.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

MouseReparenting::MouseReparenting(GameObject& parent, const char* tag, GameObject& parentA, GameObject& parentB) :
		Component(parent, tag), parentA(parentA), parentB(parentB) {}

void MouseReparenting::Start() {
	InputModule& inputModule = ModuleManager::getInstance().getModule<WindowModule>().GetInputModule();
	
	inputModule.AddMouseListener(
			MouseInput::BUTTON_LEFT, *this,
			[&gameObject = gameObject, &parentA = parentA](MouseButtonState state, int x, int y) {
				if (state == MouseButtonState::BUTTON_DOWN) {
					gameObject.Reparent(parentA);
				}
			}
	);
	
	inputModule.AddMouseListener(
			MouseInput::BUTTON_RIGHT, *this,
			[&gameObject = gameObject, &parentB = parentB](MouseButtonState state, int x, int y) {
				if (state == MouseButtonState::BUTTON_DOWN) {
					gameObject.Reparent(parentB);
				}
			}
	);
}

void MouseReparenting::Update(float delta) {}

void MouseReparenting::End() {
	InputModule& inputModule = ModuleManager::getInstance().getModule<WindowModule>().GetInputModule();

//	inputModule.RemoveMouseListener()
}
