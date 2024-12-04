//
// Created by larsv on 01/12/2024.
//

#include "MouseReparenting.hpp"

#include <utility>

#include "gameObject/GameObject.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

MouseReparenting::MouseReparenting(GameObject* parent,
								   const char* tag,
								   std::string target,
								   std::string parentA,
								   std::string parentB) :
		Component(parent, tag), target(nullptr), parentA(nullptr), parentB(nullptr),
		targetTag(std::move(target)), parentATag(std::move(parentA)), parentBTag(std::move(parentB)) {}

Component* MouseReparenting::_cloneImpl(GameObject& parent) {
	auto clone = new MouseReparenting(*this);
	return clone;
}

void MouseReparenting::Start() {
	InputModule& inputModule = ModuleManager::getInstance().getModule<WindowModule>().GetInputModule();

	target = gameObject->GetChild(targetTag, true);
	parentA = gameObject->GetChild(parentATag, true);
	parentB = gameObject->GetChild(parentBTag, true);

	inputModule.AddMouseListener(
			MouseInput::BUTTON_LEFT, *this,
			[&target = target, &parentA = parentA](MouseButtonState state, int x, int y) {
				if (state == MouseButtonState::BUTTON_DOWN && parentA && target) {
					target->Reparent(*parentA);
				}
			}
	);

	inputModule.AddMouseListener(
			MouseInput::BUTTON_RIGHT, *this,
			[&target = target, &parentB = parentB](MouseButtonState state, int x, int y) {
				if (state == MouseButtonState::BUTTON_DOWN && parentB && target) {
					target->Reparent(*parentB);
				}
			}
	);
}

void MouseReparenting::Update(float delta) {}

void MouseReparenting::End() {
	InputModule& inputModule = ModuleManager::getInstance().getModule<WindowModule>().GetInputModule();

	inputModule.RemoveMouseListener(MouseInput::BUTTON_LEFT, *this);
	inputModule.RemoveMouseListener(MouseInput::BUTTON_RIGHT, *this);
}
