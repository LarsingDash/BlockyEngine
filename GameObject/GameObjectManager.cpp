//
// Created by larsv on 24/09/2024.
//

#include "GameObjectManager.h"
#include "../Component/ExampleComponent.h"
#include <iostream>

GameObjectManager::GameObjectManager() {
	sceneRoot = new GameObject("root", nullptr);
	
	GameObject* child1 = new GameObject("Child1", sceneRoot->transform);
	child1->AddComponent<ExampleComponent>(10, 10, 255);
}

void GameObjectManager::OnUpdate(float delta) {
	sceneRoot->OnUpdate(delta);
}

GameObjectManager::~GameObjectManager() {
	delete sceneRoot;
}
