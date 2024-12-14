//
// Created by 11896 on 01/12/2024.
//

#include "MouseInputComponent.hpp"

#include <components/audio/Audio.hpp>
#include <imgui/imgui.h>
#include <components/physics/collider/CircleCollider.hpp>
#include <components/physics/rigidBody/BoxRigidBody.hpp>
#include "gameObject/GameObject.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/WindowModule.hpp"

MouseInputComponent::MouseInputComponent(GameObject* parent, const char* tag)
	: Component(parent, tag),
	  _inputModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule()),
	  _camera(ModuleManager::GetInstance().GetModule<WindowModule>().GetRenderingModule().GetCamera()),
	  _imguiModule(ModuleManager::GetInstance().GetModule<WindowModule>().GetGuiRenderingModule()) {}

Component* MouseInputComponent::_clone(const GameObject& parent) {
	auto clone = new MouseInputComponent(*this);
	return clone;
}

void MouseInputComponent::Start() {
	_inputModule.AddMouseListener(MouseInput::BUTTON_LEFT, *this, [this](MouseButtonState state, int x, int y) {
		HandleMouseInput(state, x, y, colorPalettes[currentPalette][0]);
	});
	_inputModule.AddMouseListener(MouseInput::BUTTON_RIGHT, *this, [this](MouseButtonState state, int x, int y) {
		HandleMouseInput(state, x, y, colorPalettes[currentPalette][1]);
	});
	_inputModule.AddMouseListener(MouseInput::BUTTON_MIDDLE, *this, [this](MouseButtonState state, int x, int y) {
		HandleMouseInput(state, x, y, colorPalettes[currentPalette][2]);
	});

	_imguiModule.AddComponent("pallete", [this]() {
		PaletteGUI();
	});
}

void MouseInputComponent::Update(float delta) {}

void MouseInputComponent::End() {
	_inputModule.RemoveMouseListener(MouseInput::BUTTON_LEFT, *this);
	_inputModule.RemoveMouseListener(MouseInput::BUTTON_RIGHT, *this);
	_inputModule.RemoveMouseListener(MouseInput::BUTTON_MIDDLE, *this);
	_imguiModule.RemoveComponent("pallete");
}

void MouseInputComponent::HandleMouseInput(MouseButtonState state, int x, int y, const glm::vec4& color) {
	auto& rectangle = gameObject->AddChild("Rectangle_" + std::to_string(x) + "_" + std::to_string(y));
	auto& cameraPos = _camera.GetPosition();
	rectangle.transform->SetPosition(static_cast<float>(x) + cameraPos.x, static_cast<float>(y) + cameraPos.y);

	TypeProperties physicsProperties(RIGIDBODY, false, {0, 0}, 36, 0, 0, true);

	rectangle.transform->Scale(20.f, 20.f);

	if (state == MouseButtonState::BUTTON_DOWN) {
		rectangle.AddComponent<RectangleRenderable>("rectRenderable", color, std::numeric_limits<int>::max(), true);
		rectangle.AddComponent<BoxRigidBody>("BoxRigidBody", physicsProperties);

		rectangle.AddComponent<Audio>("clowns-jingle", "../assets/audioFiles/clowns-jingle.mp3", 10, true);
		rectangle.GetComponent<Audio>("clowns-jingle")->Play();
	}
	else {
		// add the same component
		rectangle.AddComponent<Audio>("clowns-jingle", "../assets/audioFiles/car-horn.mp3", 255, false);
		rectangle.GetComponent<Audio>("clowns-jingle")->Stop();

		rectangle.AddComponent<EllipseRenderable>("ellipseRenderable", color, std::numeric_limits<int>::max(), true);
		rectangle.AddComponent<CircleCollider>("CircleRigidBody");

		rectangle.AddComponent<Audio>("squish-pop", "../assets/audioFiles/squish-pop.mp3", 255, false).Play();
		rectangle.RemoveComponent<Audio>("squish-pop");
	}
}

void MouseInputComponent::PaletteGUI() {
	ImGui::SetNextWindowSize(ImVec2(200, 100));
	ImGui::Begin("Color Palette Selector");
	if (ImGui::RadioButton("Palette 1", currentPalette == 0)) {
		currentPalette = 0;
	}
	if (ImGui::RadioButton("Palette 2", currentPalette == 1)) {
		currentPalette = 1;
	}
	if (ImGui::RadioButton("Palette 3", currentPalette == 2)) {
		currentPalette = 2;
	}

	ImGui::End();
}
