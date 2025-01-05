//
// Created by larsv on 29/12/2024.
//

#include "MouseTargetedNavigation.hpp"

#include "gameObject/GameObject.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

MouseTargetedNavigation::MouseTargetedNavigation(GameObject* gameObject, const char* tag) :
		Component(gameObject, tag, false) {}

void MouseTargetedNavigation::Start() {
	_navigator = gameObject->GetComponent<GridNavigator>();

	auto& windowModule = ModuleManager::GetInstance().GetModule<WindowModule>();
	auto& camera = windowModule.GetRenderingModule().GetCamera().GetPosition();
	windowModule.GetInputModule().AddMouseListener(
			MouseInput::BUTTON_LEFT, *this, [&navigator = _navigator, &camera]
					(MouseButtonState state, int x, int y) {
				if (state == MouseButtonState::BUTTON_UP) return;

				navigator->SetTarget(
						{
								static_cast<float>(x) + camera.x,
								static_cast<float>(y) + camera.y
						});
			}
	);
}

void MouseTargetedNavigation::Update(float delta) {}

void MouseTargetedNavigation::End() {
	ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule()
			.RemoveMouseListener(MouseInput::BUTTON_LEFT, *this);
}

Component* MouseTargetedNavigation::_clone(const GameObject& parent) {
	auto clone = new MouseTargetedNavigation(*this);
	return clone;
}