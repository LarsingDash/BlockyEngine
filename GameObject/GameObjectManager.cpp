//
// Created by larsv on 24/09/2024.
//

#include "GameObjectManager.h"
#include <iostream>

GameObjectManager::GameObjectManager() {
	sceneRoot = new GameObject("root", nullptr);
	
	GameObject* child1 = new GameObject("Child1", sceneRoot->transform);
	GameObject* child2 = new GameObject("Child2", sceneRoot->transform);
	GameObject* child2a = new GameObject("Child2a", child2->transform);
}

void GameObjectManager::OnUpdate(float delta) {
	//Recursive update
}

GameObjectManager::~GameObjectManager() {
	std::cout << "there" << std::endl;
	delete sceneRoot;
}
