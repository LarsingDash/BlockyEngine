//
// Created by larsv on 12/11/2024.
//

#include "BlockyEngine.hpp"
#include "utilities/TimeUtil.hpp"
#include <iostream>

bool BlockyEngine::isRunning{false};

BlockyEngine::BlockyEngine() : moduleManager{ModuleManager::getInstance()}, sceneManager{std::make_unique<SceneManager>()}, timeUtil(TimeUtil::CreateInstance()) {}

void BlockyEngine::Run() {
	BlockyEngine::isRunning = true;
	while (BlockyEngine::isRunning) {
		// Calculate delta time.
		float delta = timeUtil->CalculateDeltaTime();

		// Update cycle.
		sceneManager->Update(delta);
		moduleManager.Update(delta);
	}
}
