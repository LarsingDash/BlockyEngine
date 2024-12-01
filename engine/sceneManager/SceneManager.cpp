#include "SceneManager.hpp"
#include "components/animation/AnimationController.hpp"
#include "components/renderables/AnimationRenderable.hpp"
#include "moduleManager/modules/WindowModule.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "components/custom/MouseInputComponent.hpp"
#include "components/custom/KeyboardInputComponent.hpp"

SceneManager::SceneManager() :
		testScene(std::make_unique<GameObject>("root")),
		recalculationList(){
	recalculationList.reserve(25);

	auto& mouseInputComponent = testScene->AddChild("MouseInputComponent");
	mouseInputComponent.AddComponent<MouseInputComponent>("mouseInputComponent");

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

	auto& keyboardInputComponent = testScene->AddChild("KeyboardInputComponent");
	keyboardInputComponent.AddComponent<KeyboardInputComponent>("keyboardInputComponent", animatedObject);
}

void SceneManager::Update(float delta) {
	// Update active scene starting from the root
	testScene->Update(delta, recalculationList);

	// Go through all transforms that marked themselves to be recalculated
	for (auto& trans : recalculationList) {
		auto& cur = trans.get();
		if (cur.isMarkedForRecalculation) cur.RecalculateWorldMatrix();
	}
	recalculationList.clear();
}
