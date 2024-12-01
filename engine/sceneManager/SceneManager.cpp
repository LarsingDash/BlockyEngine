//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"
#include "components/animation/AnimationController.hpp"
#include "components/renderables/AnimationRenderable.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "components/example/MouseInputComponent.hpp"
#include "components/example/KeyboardInputComponent.hpp"
#include "components/example/MouseReparenting.hpp"

SceneManager::SceneManager() :
		testScene(std::make_unique<GameObject>("root")),
		recalculationList(){
	recalculationList.reserve(25);

	//Basic mouse input
	auto& mouseInputComponent = testScene->AddChild("MouseInputComponent");
	mouseInputComponent.AddComponent<MouseInputComponent>("mouseInputComponent");

	//ParentA
	auto& parentA = testScene->AddChild("ParentA");
	parentA.AddComponent<RectangleRenderable>("ParentAR", glm::vec4{255, 0, 0, 255}, true);
	parentA.transform->SetPosition(200, 300);	
	parentA.transform->SetScale(150, 300);
	parentA.transform->SetRotation(20);
	
	//ParentB
	auto& parentB = testScene->AddChild("ParentB");
	parentB.AddComponent<RectangleRenderable>("ParentBR", glm::vec4{0, 0, 255, 255}, true);
	parentB.transform->SetPosition(525, 325);
	parentB.transform->SetScale(350, 200);
	parentB.transform->SetRotation(-125);
	
	//Animated Object
	auto& animatedObject = parentA.AddChild("AnimatedObject");
	auto& animatedSprite = animatedObject.AddComponent<AnimationRenderable>(
			"animTag", "../assets/character_spritesheet.png",
			"spriteTag", 32, 32
	);

	//Animator
	auto& animationController = animatedObject.AddComponent<AnimationController>("animControllerTag", animatedSprite);
	animationController.AddAnimation("idle", 0, 11, 0.15f, true);
	animationController.AddAnimation("run", 12, 19, 0.1f, true);
	animationController.AddAnimation("jump", 27, 35, 0.1f, false);
	animatedObject.GetComponent<AnimationController>()->PlayAnimation("idle");

	//Keyboard input
	auto& keyboardInputComponent = testScene->AddChild("KeyboardInputComponent");
	keyboardInputComponent.AddComponent<KeyboardInputComponent>("keyboardInputComponent", animatedObject);
	
	//Reparenting mouse input
	animatedObject.AddComponent<MouseReparenting>("Reparenting", parentA, parentB);
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
