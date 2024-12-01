//
// Created by 11896 on 01/12/2024.
//

#include "MouseInputComponent.hpp"

MouseInputComponent::MouseInputComponent(GameObject& parent, const char* tag)
		: Component(parent, tag) {}

void MouseInputComponent::Start() {
	_inputModule.AddMouseListener(MouseInput::BUTTON_LEFT, *this, [this](MouseButtonState state, int x, int y) {
		HandleMouseInput(state, x, y, glm::vec4(255.f, 0.f, 0.f, 255.f));
	});
	_inputModule.AddMouseListener(MouseInput::BUTTON_RIGHT, *this, [this](MouseButtonState state, int x, int y) {
		HandleMouseInput(state, x, y, glm::vec4(0.f, 0.f, 255.f, 255.f));
	});
	_inputModule.AddMouseListener(MouseInput::BUTTON_MIDDLE, *this, [this](MouseButtonState state, int x, int y) {
		HandleMouseInput(state, x, y, glm::vec4(0.f, 255.f, 0.f, 255.f));
	});
}

void MouseInputComponent::Update(float delta) {
}

void MouseInputComponent::End() {
	_inputModule.RemoveMouseListener(MouseInput::BUTTON_LEFT, *this);
	_inputModule.RemoveMouseListener(MouseInput::BUTTON_RIGHT, *this);
	_inputModule.RemoveMouseListener(MouseInput::BUTTON_MIDDLE, *this);
}

void MouseInputComponent::HandleMouseInput(MouseButtonState state, int x, int y, const glm::vec4& color) {
	auto& rectangle = gameObject.AddChild("Rectangle_" + std::to_string(x) + "_" + std::to_string(y));
	rectangle.transform->SetPosition(static_cast<float>(x), static_cast<float>(y));

	if (state == MouseButtonState::BUTTON_DOWN) {
		rectangle.AddComponent<RectangleRenderable>("rectRenderable", color, true);
	} else {
		rectangle.AddComponent<EllipseRenderable>("ellipseRenderable", color, true);
	}
	rectangle.transform->SetScale(20.f, 20.f);
}
