//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"
#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/animation/AnimationController.hpp"
#include "components/renderables/AnimationRenderable.hpp"
#include "moduleManager/modules/WindowModule.hpp"
#include "moduleManager/ModuleManager.hpp"

SceneManager::SceneManager() :
		testScene(std::make_unique<GameObject>("root")),
		recalculationList(),
		_inputModule(ModuleManager::getInstance().getModule<WindowModule>().GetInputModule()) {
	recalculationList.reserve(25);

	_inputModule.AddMouseListener([this](const MouseEvent& mouseEvent) {
		auto& rectangle =
				testScene->AddChild("Rectangle_" + std::to_string(mouseEvent.x) + "_" + std::to_string(mouseEvent.y));
		rectangle.transform->SetPosition(static_cast<float>(mouseEvent.x), static_cast<float>(mouseEvent.y));

		glm::vec4 color;
		if (mouseEvent.button == MouseInput::BUTTON_LEFT) {
			color = glm::vec4(255.f, 0.f, 0.f, 255.f);
		} else if (mouseEvent.button == MouseInput::BUTTON_RIGHT) {
			color = glm::vec4(0.f, 0.f, 255.f, 255.f);
		} else if (mouseEvent.button == MouseInput::BUTTON_MIDDLE) {
			color = glm::vec4(0.f, 255.f, 0.f, 255.f);
		}

		if (mouseEvent.state == MouseButtonState::BUTTON_DOWN) {
			rectangle.AddComponent<RectangleRenderable>("rectRenderable", color, true);
			rectangle.transform->SetScale(20.f, 20.f);
		} else {
			rectangle.AddComponent<EllipseRenderable>("ellipseRenderable", color, true);
			rectangle.transform->SetScale(20.f, 20.f);
		}

	});



	// Animations
	auto& animatedObject = testScene->AddChild("AnimatedObject");
	animatedObject.transform->SetScale(200.f, 200.f);
	animatedObject.transform->SetPosition(100.f, 100.f);
	auto& animatedSprite = animatedObject.AddComponent<AnimationRenderable>(
			"animTag", "../assets/character_spritesheet.png",
			"spriteTag", 32, 32
	);
	auto& animationController = animatedObject.AddComponent<AnimationController>("animControllerTag", animatedSprite);

	animationController.AddAnimation("idle", 0, 11, 0.15f, true);
	animationController.AddAnimation("run", 12, 19, 0.1f, true);
	animationController.AddAnimation("jump", 27, 35, 0.1f, false);

	animatedObject.GetComponent<AnimationController>()->PlayAnimation("idle");

	_inputModule.AddKeyListener([&animationController](KeyEvent event) {
		if (event.state == KeyState::KEY_DOWN && event.key == KeyInput::KEY_Q) {
			animationController.PlayAnimation("idle");
		}
		if (event.state == KeyState::KEY_DOWN && event.key == KeyInput::KEY_W) {
			animationController.PlayAnimation("run");
		}
		if (event.state == KeyState::KEY_DOWN && event.key == KeyInput::KEY_E) {
			animationController.PlayAnimation("jump");
		}
	});

}

void SceneManager::Update(float delta) {
	//Update active scene starting from the root
	testScene->Update(delta, recalculationList);

	//Go through all transforms that marked themselves to be recalculated
	for (auto& trans : recalculationList) {
		auto& cur = trans.get();
		if (cur.isMarkedForRecalculation) cur.RecalculateWorldMatrix();
	}
	recalculationList.clear();
}