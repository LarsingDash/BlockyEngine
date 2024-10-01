//
// Created by larsv on 24/09/2024.
//

#include "GameObjectManager.h"
#include "../Component/ExampleComponent.h"
#include "../Component/OtherComponent.h"
#include <iostream>

GameObjectManager::GameObjectManager() : sceneRoot(std::make_unique<GameObject>("root")) {	
	//HIERARCHY TEST
	GameObject& child1 = sceneRoot->AddChild("Child1");
	GameObject& child2 = sceneRoot->AddChild("Child2");
	GameObject& child3 = child2.AddChild("Child3");
	child2.SetParent(child1);
	child3.SetParent(child1);
	sceneRoot->RemoveChild(child1);
	
	//COMPONENT TEST
//	GameObject& child1 = sceneRoot->AddChild("Child1");
//	std::cout << "Add first of Example, 0: " << (child1.AddComponent<ExampleComponent>(10, 10, 0) == nullptr) << std::endl;
//	std::cout << "Add first of Other, 0: " << (child1.AddComponent<OtherComponent>(160, 10, 255) == nullptr) << std::endl;
//	std::cout << "Add second of Other, 1: "<< (child1.AddComponent<OtherComponent>(160, 10, 255) == nullptr) << std::endl;
//	std::cout << "Remove example" << std::endl;
//	child1.RemoveComponent<ExampleComponent>();
//	std::cout << "Add second of Example, 0: "<< (child1.AddComponent<ExampleComponent>(10, 160, 155) == nullptr) << std::endl;
}

void GameObjectManager::OnUpdate(float delta) {
	sceneRoot->OnUpdate(delta);
}
