//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

SceneManager::SceneManager() : testScene{} {
	testScene.emplace_back(std::make_unique<GameObject>("object1"));
}

void SceneManager::Update(float delta) {
	for (auto& gameObject : testScene) {
		gameObject->Update(delta);
	}
}
