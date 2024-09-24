//
// Created by larsv on 24/09/2024.
//

#include "GameObjectManager.h"
#include "../Component/ExampleComponent.h"
#include <iostream>

GameObjectManager::GameObjectManager() {
	sceneRoot = new GameObject("root", nullptr);
	
//	GameObject* child1 = new GameObject("Child1", sceneRoot->transform);
//	GameObject* child2 = new GameObject("Child2", sceneRoot->transform);
//	GameObject* child2A = new GameObject("Child2A", child2->transform);
	auto* childA = new GameObject("ChildA", sceneRoot->transform);
	auto* componentA = childA->AddComponent<ExampleComponent>(150, 150, 100);

	auto* childB = new GameObject("ChildB", childA->transform);
	auto* componentB = childB->AddComponent<ExampleComponent>(150, 300, 200);

	auto* childC = new GameObject("ChildC", sceneRoot->transform);
	auto* componentC = childC->AddComponent<ExampleComponent>(300, 150, 150);
}

void GameObjectManager::OnUpdate(float delta) {
	sceneRoot->OnUpdate(delta);
}

GameObjectManager::~GameObjectManager() {
	std::cout << "there" << std::endl;
	delete sceneRoot;
}
