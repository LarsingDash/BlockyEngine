﻿//
// Created by larsv on 24/09/2024.
//

#include "GameObjectManager.h"
#include "../Component/ExampleComponent.h"
#include "../Component/OtherComponent.h"
#include <iostream>

GameObjectManager::GameObjectManager() : sceneRoot(std::make_unique<GameObject>("root")) {	
	GameObject& child1 = sceneRoot->AddChild("Child1");
	GameObject& child2 = sceneRoot->AddChild("Child2");
	std::cout << "Root\n" << "\t1\n" << "\t2\n" << std::endl;
	
	child2.SetParent(child1);
	std::cout << "Root\n" << "\t1\n" << "\t\t2\n" << std::endl;

	auto* example = child1.AddComponent<ExampleComponent>(10, 10, 255);
	std::cout << "Add first of Example, 0: " << (example == nullptr) << std::endl;
	std::cout << "Add first of Other, 0: " << (child1.AddComponent<OtherComponent>(160, 10, 255) == nullptr) << std::endl;
	std::cout << "Add second of Other, 1: "<< (child1.AddComponent<OtherComponent>(160, 10, 255) == nullptr) << std::endl;

	std::cout << "Remove example" << std::endl;
	child1.RemoveComponent<ExampleComponent>();
	std::cout << "Add second of Example, 0: "<< (child1.AddComponent<ExampleComponent>(10, 160, 255) == nullptr) << std::endl;
}

void GameObjectManager::OnUpdate(float delta) {
	sceneRoot->OnUpdate(delta);
}