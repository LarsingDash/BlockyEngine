//
// Created by larsv on 10/12/2024.
//

#include "MouseCameraController.hpp"

#include "BlockyEngine.hpp"
#include "gameObject/GameObject.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"
#include "moduleManager/modules/input/InputModule.hpp"

MouseCameraController::MouseCameraController(GameObject* gameObject, const char* tag) :
		Component(gameObject, tag, false),
		_threshold(static_cast<float>(BlockyEngine::GetConfigs()->windowWidth) * 0.25f / 2.f,
				   static_cast<float>(BlockyEngine::GetConfigs()->windowHeight) * 0.25f / 2.f),
		_middle(BlockyEngine::GetConfigs()->windowWidth / 2, BlockyEngine::GetConfigs()->windowHeight / 2),
		_camera(ModuleManager::GetInstance().GetModule<WindowModule>().GetRenderingModule().GetCamera()),
		_inputModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule()) {}

void MouseCameraController::Start() {
	_camera.SetPosition(0.f, 0.f);
	_camera.SetBoundary(
			static_cast<float>(BlockyEngine::GetConfigs()->windowWidth) / 2.f,
			static_cast<float>(BlockyEngine::GetConfigs()->windowHeight) / 2.f
	);
}

void MouseCameraController::Update(float delta) {
	//Get dif
	glm::vec2 position = static_cast<glm::vec2>(InputModule::GetCursorPosition()) - _middle;

	//Threshold x
	if (position.x < 0) position.x = std::min(0.f, position.x + _threshold.x);
	else position.x = std::max(0.f, position.x - _threshold.x);
	if (position.y < 0) position.y = std::min(0.f, position.y + _threshold.y);
	else position.y = std::max(0.f, position.y - _threshold.y);

	position *= .5f * delta;

	_camera.Translate(position.x, position.y);
}

void MouseCameraController::End() {}

Component* MouseCameraController::_clone(const GameObject& parent) {
	auto clone = new MouseCameraController(*this);
	return clone;
}